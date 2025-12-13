#pragma once

#include "Event.h"
#include <functional>
#include <string>

namespace core
{
    struct WindowSpecification
    {
        std::string Title;
        uint32_t Width = 1280;
        uint32_t Height = 720;
        bool IsResizeable = true;
        bool VSync = true;

        using EventCallbackFn = std::function<void(Event&)>;
        EventCallbackFn EventCallback;
    };

    class Window
    {
    public:
        Window(const WindowSpecification& specification = WindowSpecification());
        ~Window();

        void Create();
        void Destroy();
        void Update();
        void RaiseEvent(Event& event);
        bool ShouldClose() const;

    private:
        WindowSpecification m_Specification;
    };

}
