#include "Window.hpp"
#include "core/events/KeyboardEvents.hpp"
#include "core/events/MouseEvents.hpp"
#include "core/events/WindowEvents.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <SDL3/SDL.h>

namespace core
{
    Window::Window(const WindowSpecification& specification)
        : m_Specification(specification)
    {
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Create()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != true)
        {
            core::utils::Logger::error("SDL_Init failed: {}", SDL_GetError());
            return;
        }

        auto windowFlags = SDL_WINDOW_RESIZABLE;
        if (m_Specification.Title.empty())
            m_Specification.Title = "String Art App";

        m_Window = SDL_CreateWindow(m_Specification.Title.c_str(),
            m_Specification.Width,
            m_Specification.Height,
            windowFlags);

        if (!m_Window)
        {
            core::utils::Logger::error("CreateWindow failed: {}", SDL_GetError());
            return;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
        if (!m_Renderer)
        {
            core::utils::Logger::error("CreateRenderer failed: {}", SDL_GetError());
            return;
        }

        // VSync
        SDL_SetRenderVSync(m_Renderer, m_Specification.VSync ? 1 : 0);

        core::utils::Logger::info("Window created: {} ({}, {})", m_Specification.Title, m_Specification.Width, m_Specification.Height);
    }

    void Window::Destroy()
    {
        if (m_Renderer)
        {
            SDL_DestroyRenderer(m_Renderer);
            m_Renderer = nullptr;
        }

        if (m_Window)
        {
            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
        }

        SDL_Quit();
    }

    void Window::Update()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                {
                    WindowCloseEvent e;
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    m_ShouldClose = true;
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    WindowResizeEvent e(event.window.data1, event.window.data2);
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION:
                {
                    MouseMovedEvent e(static_cast<double>(event.motion.x), static_cast<double>(event.motion.y));
                    // utils::Logger::trace(e.ToString()); // Too verbose for mouse move
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_MOUSE_WHEEL:
                {
                    MouseScrolledEvent e(static_cast<double>(event.wheel.x), static_cast<double>(event.wheel.y));
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                {
                    MouseButtonPressedEvent e(static_cast<int>(event.button.button));
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP:
                {
                    MouseButtonReleasedEvent e(static_cast<int>(event.button.button));
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_KEY_DOWN:
                {
                    bool isRepeat = event.key.repeat != 0;
                    KeyPressedEvent e(static_cast<uint32_t>(event.key.key), isRepeat);
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    KeyReleasedEvent e(static_cast<uint32_t>(event.key.key));
                    utils::Logger::trace(e.ToString());
                    RaiseEvent(e);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Window::RaiseEvent(Event& event)
    {
        if (m_Specification.EventCallback)
            m_Specification.EventCallback(event);
    }
}
