#include "Renderer.hpp"
#include "utils/LoggerConfig.hpp"

namespace app
{
    Renderer::Renderer(const model::Configs& configs)
        : m_renderer(nullptr)
        , m_window(nullptr)
    {
        initialize(configs);
    }

    bool Renderer::initialize(const model::Configs& configs)
    {
        auto windowsFlags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;

        m_window = SDL_CreateWindow(configs.windowTitle.c_str(), configs.windowWidth, configs.windowHeight, windowsFlags);
        if (!m_window)
        {
            utils::logger::error("CreateWindow failed: {}", SDL_GetError());
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer)
        {
            utils::logger::error("CreateRenderer failed: {}", SDL_GetError());
            SDL_DestroyWindow(m_window);
            return false;
        }

        return true;
    }

    Renderer::~Renderer()
    {
        destroy();
    }

    void Renderer::clear()
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
    }

    void Renderer::destroy()
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

    SDL_Renderer* Renderer::getRenderer()
    {
        return m_renderer;
    }

    SDL_Window* Renderer::getWindow()
    {
        return m_window;
    }

    void Renderer::render()
    {
        SDL_RenderClear(m_renderer);

        SDL_RenderPresent(m_renderer);
    }
}
