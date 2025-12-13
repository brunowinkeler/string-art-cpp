#include "Window.h"
#include "core/events/ApplicationEvent.h"
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
        // SDL_SetRenderVSync(m_Renderer, m_Specification.VSync ? 1 : 0);

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
                    m_Specification.EventCallback(e);
                    m_ShouldClose = true;
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    WindowResizeEvent e(event.window.data1, event.window.data2);
                    m_Specification.EventCallback(e);
                    break;
                }
                    // TODO: Add Key and Mouse events here
            }
        }

        if (m_Renderer)
        {
            SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_Renderer);

            // Rendering happens in layers, but the present happens here or in Application?
            // Usually Application controls the flow.
            // For now, let's just present here to ensure window works,
            // but ideally layers draw to this renderer before Present.

            SDL_RenderPresent(m_Renderer);
        }
    }
}
