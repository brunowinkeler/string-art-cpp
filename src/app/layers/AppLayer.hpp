#pragma once

#include "core/Layer.hpp"
#include "core/resources/FontManager.hpp"
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
        // Render AppLayer stuff
    }

private:
    void LoadResources()
    {
        core::utils::Logger::info("Loading textures and fonts for AppLayer...");
        // core::FontManager::Load("Arial", "assets/fonts/arial.ttf", 16);
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
