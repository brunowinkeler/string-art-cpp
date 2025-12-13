#pragma once

#include "core/events/Event.h"
#include <cstdint>
#include <functional>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

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

        SDL_Window* GetNativeWindow() const
        {
            return m_Window;
        }

        SDL_Renderer* GetRenderer() const
        {
            return m_Renderer;
        }

        bool ShouldClose() const
        {
            return m_ShouldClose;
        }

    private:
        WindowSpecification m_Specification;
        SDL_Window* m_Window = nullptr;
        SDL_Renderer* m_Renderer = nullptr;
        bool m_ShouldClose = false;
    };

}
