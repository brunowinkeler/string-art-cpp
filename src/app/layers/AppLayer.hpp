#pragma once

#include "core/Layer.hpp"
#include "core/imaging/ImageConverter.hpp"
#include "core/imaging/ImageModifier.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/resources/FontManager.hpp"
#include "core/resources/SurfaceManager.hpp"
#include "core/utils/LoggerConfig.hpp"

class AppLayer : public core::Layer
{
public:
    AppLayer()
        : Layer("AppLayer")
    {}

    void OnAttach() override
    {
        core::utils::Logger::info("AppLayer Attached!");

        LoadResources();
        ResetSimulationState();
    }

    void OnDetach() override
    {
        // Dont include logging here because maybe it will be called after the shutdown of the logger
    }

    void OnUpdate(float ts) override
    {
        // core::utils::Logger::info("AppLayer Update");
    }

    void OnRender() override
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

private:
    std::shared_ptr<core::Texture2D> m_ProcessedTexture;

    void LoadResources()
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

    void ResetSimulationState()
    {
        core::utils::Logger::info("Resetting simulation variables...");
        // m_NailCount = 200;
    }

    void OnEvent(core::Event& event) override
    {
        // core::utils::Logger::info("AppLayer Event: {}", event.ToString());
    }
};
