#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

#include "model/Configs.hpp"
#include <SDL3/SDL.h>

namespace app
{
    class Renderer
    {
    public:
        Renderer(const model::Configs& configs);
        ~Renderer();

        bool initialize(const model::Configs& configs);
        void render();
        void clear();
        void destroy();

        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();

    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
    };
}

#endif // APP_RENDERER_HPP
