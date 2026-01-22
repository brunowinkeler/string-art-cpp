#include "AppLayer.hpp"
#include "core/events/KeyboardEvents.hpp"
#include "core/events/WindowEvents.hpp"
#include "core/imaging/ImageConverter.hpp"
#include "core/imaging/ImageModifier.hpp"
#include "core/resources/SurfaceManager.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace app
{
    AppLayer::AppLayer()
        : Layer("AppLayer")
    {}

    void AppLayer::OnAttach()
    {
        core::utils::Logger::info("AppLayer Attached!");
        LoadResources();
        InitializeGenerator();
    }

    void AppLayer::OnDetach()
    {
    }

    void AppLayer::OnUpdate(float /*ts*/)
    {
        auto& state = m_Generator.GetState();
        if (state.isRunning && !state.isComplete)
        {
            for (int i = 0; i < m_LinesPerFrame; ++i)
            {
                if (!m_Generator.Step())
                    break;
            }
        }
    }

    void AppLayer::OnRender()
    {
        core::Renderer::SetDrawColor(255, 255, 255, 255);
        core::Renderer::Clear();

        RenderStringArt();
        RenderNails();
    }

    void AppLayer::LoadResources()
    {
        core::utils::Logger::info("Loading resources...");

        auto surface = core::SurfaceManager::Load("OriginalImage", "assets/images/woman.png");
        if (!surface)
        {
            core::utils::Logger::error("Failed to load image");
            return;
        }

        auto graySurface = core::imaging::ImageConverter::ConvertToGrayscale(surface.get());
        if (!graySurface)
        {
            core::utils::Logger::error("Failed to convert to grayscale");
            return;
        }

        int radius = std::min(graySurface->w, graySurface->h) / 2;
        core::imaging::ImageModifier::ApplyCircularMask(graySurface.get(), radius);

        m_SourceSurface = std::shared_ptr<SDL_Surface>(graySurface.release(), SDL_DestroySurface);
        m_SourceTexture = std::make_shared<core::Texture2D>(m_SourceSurface.get());

        core::utils::Logger::info("Resources loaded successfully");
    }

    void AppLayer::InitializeGenerator()
    {
        if (!m_SourceSurface)
        {
            core::utils::Logger::error("Cannot initialize generator: no source surface");
            return;
        }

        m_Generator.Initialize(m_SourceSurface.get(), m_NumNails, m_MaxLines);

        m_OffsetX = (1280.0f - m_SourceSurface->w) / 2.0f;
        m_OffsetY = (720.0f - m_SourceSurface->h) / 2.0f;

        core::utils::Logger::info("Generator initialized with {} nails, {} max lines", m_NumNails, m_MaxLines);
    }

    void AppLayer::RenderStringArt()
    {
        if (!m_Generator.IsInitialized())
            return;

        const auto& state = m_Generator.GetState();
        const auto& nailCircle = m_Generator.GetNailCircle();

        core::Renderer::SetDrawColor(0, 0, 0, 20);

        for (size_t i = 1; i < state.path.size(); ++i)
        {
            const auto& from = nailCircle.GetNail(state.path[i - 1]);
            const auto& to = nailCircle.GetNail(state.path[i]);

            core::Renderer::DrawLine(
                m_OffsetX + from.m_x,
                m_OffsetY + from.m_y,
                m_OffsetX + to.m_x,
                m_OffsetY + to.m_y);
        }
    }

    void AppLayer::RenderNails()
    {
        if (!m_Generator.IsInitialized())
            return;

        const auto& nails = m_Generator.GetNailCircle().GetNails();

        core::Renderer::SetDrawColor(100, 100, 100, 255);

        for (const auto& nail : nails)
        {
            float x = m_OffsetX + nail.m_x;
            float y = m_OffsetY + nail.m_y;
            core::Renderer::FillRect(x - 2, y - 2, 4, 4);
        }
    }

    void AppLayer::OnEvent(core::Event& event)
    {
        core::EventDispatcher dispatcher(event);

        dispatcher.Dispatch<core::WindowResizeEvent>([this](core::WindowResizeEvent& e)
            {
                if (m_SourceSurface)
                {
                    m_OffsetX = (e.GetWidth() - m_SourceSurface->w) / 2.0f;
                    m_OffsetY = (e.GetHeight() - m_SourceSurface->h) / 2.0f;
                }
                return false;
            });

        dispatcher.Dispatch<core::KeyPressedEvent>([this](core::KeyPressedEvent& e)
            {
                if (e.IsRepeat())
                    return false;

                switch (e.GetKeyCode())
                {
                    case SDLK_SPACE:
                    {
                        auto& state = const_cast<model::SimulationState&>(m_Generator.GetState());
                        state.isRunning = !state.isRunning;
                        core::utils::Logger::info("Simulation {}", state.isRunning ? "started" : "paused");
                        break;
                    }
                    case SDLK_R:
                    {
                        m_Generator.Reset();
                        InitializeGenerator();
                        core::utils::Logger::info("Simulation reset");
                        break;
                    }
                    default:
                        break;
                }
                return false;
            });
    }
} // namespace app
