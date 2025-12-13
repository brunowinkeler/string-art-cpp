#pragma once

#include "core/Layer.h"
#include "core/utils/LoggerConfig.hpp"

class OverlayLayer : public core::Layer
{
public:
    OverlayLayer()
        : Layer("OverlayLayer")
    {}

    void OnAttach() override
    {
        core::utils::Logger::info("OverlayLayer Attached!");
    }

    void OnUpdate(float ts) override
    {
    }

    void OnRender() override
    {
        // Render UI/Overlay
    }

    void OnEvent(core::Event& event) override
    {
    }
};
