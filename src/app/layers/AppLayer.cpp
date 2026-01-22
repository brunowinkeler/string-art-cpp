#include "AppLayer.hpp"
#include "core/events/WindowEvents.hpp"

namespace app
{
    AppLayer::AppLayer()
        : Layer("AppLayer")
    {}

    void AppLayer::OnAttach()
    {
        core::utils::Logger::info("AppLayer Attached!");

        LoadResources();
        ResetSimulationState();
    }

    void AppLayer::OnDetach()
    {
        // Dont include logging here because maybe it will be called after the shutdown of the logger
    }

    void AppLayer::OnUpdate(float /*ts*/)
    {
        // core::utils::Logger::info("AppLayer Update");
    }

    void AppLayer::OnRender()
    {
        core::Renderer::SetDrawColor(30, 30, 30, 255);
        core::Renderer::Clear();

        if (m_ProcessedTexture)
        {
            float x = (800.0f - m_ProcessedTexture->GetWidth()) / 2.0f;
            float y = (600.0f - m_ProcessedTexture->GetHeight()) / 2.0f;
            core::Renderer::DrawTexture(m_ProcessedTexture, x, y,
                (float)m_ProcessedTexture->GetWidth(),
                (float)m_ProcessedTexture->GetHeight());
        }
    }

    void AppLayer::LoadResources()
    {
        core::utils::Logger::info("Loading textures and fonts for AppLayer...");

        auto originalSurface = core::SurfaceManager::Load("OriginalImage", "assets/images/woman.png");
        if (originalSurface)
        {
            auto graySurfacePtr = core::imaging::ImageConverter::ConvertToGrayscale(originalSurface.get());

            if (graySurfacePtr)
            {
                int radius = std::min(graySurfacePtr->w, graySurfacePtr->h) / 2;
                core::imaging::ImageModifier::ApplyCircularMask(graySurfacePtr.get(), radius);

                m_ProcessedTexture = std::make_shared<core::Texture2D>(graySurfacePtr.get());

                core::utils::Logger::info("Image processed successfully!");
            }
        }
        else
        {
            core::utils::Logger::error("Failed to load 'monalisa.jpg'. Make sure the file exists in assets/images/");
        }
    }

    void app::AppLayer::ResetSimulationState()
    {
        core::utils::Logger::info("Simulation state reset.");
    }

    void AppLayer::OnEvent(core::Event& event)
    {
        core::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<core::WindowResizeEvent>([](core::WindowResizeEvent& e)
            {
                core::utils::Logger::info("Window resized to: {}x{}", e.GetWidth(), e.GetHeight());
                return false;
            });
        // core::utils::Logger::info("AppLayer received event: {}", event.ToString());
    }
} // namespace app
