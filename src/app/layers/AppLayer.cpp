#include "AppLayer.hpp"
#include "app/io/ConfigsReader.hpp"
#include "core/Application.hpp"
#include "core/events/KeyboardEvents.hpp"
#include "core/imaging/ImageModifier.hpp"
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>

namespace app
{
    AppLayer::AppLayer()
        : Layer("AppLayer")
    {}

    void AppLayer::OnAttach()
    {
        LoadConfigs();
        LoadResources();
        InitializeGenerator();
        UpdateLayout();
    }

    void AppLayer::OnDetach()
    {
        if (m_SourceTexture)
        {
            SDL_DestroyTexture(m_SourceTexture);
            m_SourceTexture = nullptr;
        }
    }

    void AppLayer::OnUpdate(float)
    {
        const auto& state = m_Generator.GetState();
        if (!state.isRunning || state.isComplete)
            return;

        for (int i = 0; i < m_Configs.linesPerFrame; ++i)
        {
            if (m_Generator.GetState().isComplete)
                break;
            bool stepped = m_Generator.Step();
            if (!stepped)
            {
                spdlog::warn("Step failed at line {}", m_Generator.GetState().linesDrawn);
                break;
            }
        }

        static int lastLogged = 0;
        if (state.linesDrawn / 100 > lastLogged)
        {
            lastLogged = state.linesDrawn / 100;
            spdlog::info("Lines drawn: {}", state.linesDrawn);
        }
    }

    void AppLayer::OnRender()
    {
        auto& app = core::Application::Get();
        SDL_Renderer* renderer = app.GetWindow().GetRenderer();

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        RenderSourceCircle();
        RenderReconstructedCircle();

        SDL_RenderPresent(renderer);
    }

    void AppLayer::OnEvent(core::Event& event)
    {
        core::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<core::KeyPressedEvent>([this](core::KeyPressedEvent& e)
            {
                if (e.IsRepeat())
                    return false;

                switch (e.GetKeyCode())
                {
                    case SDLK_SPACE:
                    {
                        const auto& state = m_Generator.GetState();
                        if (!state.isRunning)
                        {
                            m_Generator.Start();
                            spdlog::info("Started simulation");
                        }
                        else
                        {
                            m_Generator.ToggleRunning();
                            spdlog::info(m_Generator.GetState().isRunning ? "Resumed" : "Paused");
                        }
                    }
                    break;
                    case SDLK_R:
                        m_Generator.Reset();
                        spdlog::info("Reset simulation");
                        break;
                    case SDLK_Q:
                        m_Zoom = std::max(0.1f, m_Zoom - 0.1f);
                        spdlog::info("Zoom: {:.1f}", m_Zoom);
                        break;
                    case SDLK_E:
                        m_Zoom = std::min(5.0f, m_Zoom + 0.1f);
                        spdlog::info("Zoom: {:.1f}", m_Zoom);
                        break;
                    case SDLK_F:
                        m_Zoom = 1.0f;
                        spdlog::info("Zoom reset to 1.0");
                        break;
                }
                return true;
            });
    }

    void AppLayer::LoadConfigs()
    {
        io::ConfigsReader reader;
        reader.ScanConfigsFile("configurations/default_configs.json");
        m_Configs = reader.GetConfigs();
        spdlog::info("Configs loaded: {}x{}, {} nails, {} lines",
            m_Configs.windowWidth, m_Configs.windowHeight,
            m_Configs.numNails, m_Configs.numLinesToDraw);
    }

    void AppLayer::LoadResources()
    {
        SDL_Surface* rawSurface = IMG_Load(m_Configs.inputImagePath.c_str());
        if (!rawSurface)
        {
            spdlog::error("Failed to load image: {}", m_Configs.inputImagePath);
            return;
        }

        int maxDim = std::min(m_Configs.windowWidth / 2 - 40, m_Configs.windowHeight - 40);
        auto scaled = core::imaging::ImageModifier::ScaleToFit(rawSurface, maxDim, maxDim);
        SDL_DestroySurface(rawSurface);

        if (!scaled)
        {
            spdlog::error("Failed to scale image");
            return;
        }

        m_SourceSurface = std::shared_ptr<SDL_Surface>(scaled.release(), SDL_DestroySurface);
        m_CircleRadius = std::min(m_SourceSurface->w, m_SourceSurface->h) / 2;

        auto& app = core::Application::Get();
        SDL_Renderer* renderer = app.GetWindow().GetRenderer();
        m_SourceTexture = SDL_CreateTextureFromSurface(renderer, m_SourceSurface.get());
        if (!m_SourceTexture)
        {
            spdlog::error("Failed to create texture: {}", SDL_GetError());
        }

        spdlog::info("Image loaded and scaled: {}x{}, radius={}",
            m_SourceSurface->w, m_SourceSurface->h, m_CircleRadius);
    }

    void AppLayer::InitializeGenerator()
    {
        if (!m_SourceSurface)
            return;

        m_Generator.Initialize(
            m_SourceSurface.get(),
            m_Configs.numNails,
            m_Configs.numLinesToDraw,
            m_Configs.darkenAmount,
            m_Configs.minNailDistance);
        spdlog::info("Generator initialized");
    }

    void AppLayer::UpdateLayout()
    {
        float halfWidth = m_Configs.windowWidth / 2.0f;
        float centerY = m_Configs.windowHeight / 2.0f;

        m_LeftOffsetX = halfWidth / 2.0f;
        m_LeftOffsetY = centerY;

        m_RightOffsetX = halfWidth + halfWidth / 2.0f;
        m_RightOffsetY = centerY;
    }

    void AppLayer::RenderSourceCircle()
    {
        if (!m_SourceSurface)
            return;

        auto& app = core::Application::Get();
        SDL_Renderer* renderer = app.GetWindow().GetRenderer();

        float radius = m_CircleRadius * m_Zoom;
        float cx = m_LeftOffsetX;
        float cy = m_LeftOffsetY;

        if (m_SourceTexture)
        {
            float imgSize = m_SourceSurface->w * m_Zoom;
            SDL_FRect destRect = {
                cx - imgSize / 2.0f,
                cy - imgSize / 2.0f,
                imgSize,
                imgSize
            };
            SDL_RenderTexture(renderer, m_SourceTexture, nullptr, &destRect);
        }

        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        for (int i = 0; i < 360; ++i)
        {
            float a1 = i * std::numbers::pi_v<float> / 180.0f;
            float a2 = (i + 1) * std::numbers::pi_v<float> / 180.0f;
            SDL_RenderLine(renderer,
                cx + radius * std::cos(a1), cy + radius * std::sin(a1),
                cx + radius * std::cos(a2), cy + radius * std::sin(a2));
        }

        RenderNails(cx, cy);

        const auto& state = m_Generator.GetState();
        if (state.path.size() > 1)
        {
            SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
            const auto& nails = m_Generator.GetNailCircle();
            for (size_t i = 1; i < state.path.size(); ++i)
            {
                auto [x1, y1] = nails.GetNail(state.path[i - 1]);
                auto [x2, y2] = nails.GetNail(state.path[i]);
                SDL_RenderLine(renderer,
                    cx + (x1 - m_CircleRadius) * m_Zoom,
                    cy + (y1 - m_CircleRadius) * m_Zoom,
                    cx + (x2 - m_CircleRadius) * m_Zoom,
                    cy + (y2 - m_CircleRadius) * m_Zoom);
            }
        }
    }

    void AppLayer::RenderReconstructedCircle()
    {
        auto& app = core::Application::Get();
        SDL_Renderer* renderer = app.GetWindow().GetRenderer();

        float radius = m_CircleRadius * m_Zoom;
        float cx = m_RightOffsetX;
        float cy = m_RightOffsetY;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 360; ++i)
        {
            float a1 = i * M_PI / 180.0f;
            float a2 = (i + 1) * M_PI / 180.0f;
            SDL_RenderLine(renderer,
                cx + radius * std::cos(a1), cy + radius * std::sin(a1),
                cx + radius * std::cos(a2), cy + radius * std::sin(a2));
        }

        RenderNails(cx, cy);

        const auto& state = m_Generator.GetState();
        if (state.path.size() > 1)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            const auto& nails = m_Generator.GetNailCircle();
            for (size_t i = 1; i < state.path.size(); ++i)
            {
                auto [x1, y1] = nails.GetNail(state.path[i - 1]);
                auto [x2, y2] = nails.GetNail(state.path[i]);
                SDL_RenderLine(renderer,
                    cx + (x1 - m_CircleRadius) * m_Zoom,
                    cy + (y1 - m_CircleRadius) * m_Zoom,
                    cx + (x2 - m_CircleRadius) * m_Zoom,
                    cy + (y2 - m_CircleRadius) * m_Zoom);
            }
        }
    }

    void AppLayer::RenderNails(float offsetX, float offsetY)
    {
        auto& app = core::Application::Get();
        SDL_Renderer* renderer = app.GetWindow().GetRenderer();

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        const auto& nails = m_Generator.GetNailCircle();
        for (int i = 0; i < nails.GetCount(); ++i)
        {
            auto [x, y] = nails.GetNail(i);
            float sx = offsetX + (x - m_CircleRadius) * m_Zoom;
            float sy = offsetY + (y - m_CircleRadius) * m_Zoom;
            SDL_RenderLine(renderer, sx - 2, sy, sx + 2, sy);
            SDL_RenderLine(renderer, sx, sy - 2, sx, sy + 2);
        }
    }
} // namespace app
