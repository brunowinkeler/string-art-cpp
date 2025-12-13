#include "Renderer.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace app
{
    Renderer::Renderer(const model::Configs& configs)
        : m_renderer(nullptr)
        , m_window(nullptr)
    {
        Initialize(configs);
    }

    bool Renderer::Initialize(const model::Configs& configs)
    {
        auto windowsFlags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;

        m_window = SDL_CreateWindow(configs.windowTitle.c_str(), configs.windowWidth, configs.windowHeight, windowsFlags);
        if (!m_window)
        {
            core::utils::Logger::error("CreateWindow failed: {}", SDL_GetError());
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer)
        {
            core::utils::Logger::error("CreateRenderer failed: {}", SDL_GetError());
            SDL_DestroyWindow(m_window);
            return false;
        }

        return true;
    }

    Renderer::~Renderer()
    {
        Destroy();
    }

    void Renderer::Clear()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
    }

    void Renderer::Destroy()
    {
        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }

        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    SDL_Renderer* Renderer::GetRenderer()
    {
        return m_renderer;
    }

    SDL_Window* Renderer::GetWindow()
    {
        return m_window;
    }

    void Renderer::Render()
    {
        SDL_RenderClear(m_renderer);

        SDL_RenderPresent(m_renderer);
    }
}
