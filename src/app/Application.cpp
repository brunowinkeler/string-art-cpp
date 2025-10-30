#include "Application.hpp"
#include "SDL3_ttf/SDL_ttf.h"

namespace app
{
    Application::Application()
        : m_renderer(nullptr)
        , m_window(nullptr)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != true)
        {
            SDL_Log("SDL_Init failed: %s", SDL_GetError());
            exit(1);
        }

        // SDL_ttf
        if (TTF_Init() != true)
        {
            SDL_Log("TTF_Init failed: %s", SDL_GetError());
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }

        m_window = SDL_CreateWindow("SDL3 File Dialog + Image + Path", 960, 640, SDL_WINDOW_RESIZABLE);
        if (!m_window)
        {
            SDL_Log("CreateWindow failed: %s", SDL_GetError());
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer)
        {
            SDL_Log("CreateRenderer failed: %s", SDL_GetError());
            SDL_DestroyWindow(m_window);
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }
    }

    Application::~Application()
    {
        // Clean up SDL
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
    }

    void Application::run()
    {
        // Main application loop
        bool running = true;
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    running = false;
                }
            }

            // Update and render
            SDL_RenderClear(m_renderer);
            // Render your application content here
            SDL_RenderPresent(m_renderer);
        }
    }
}
