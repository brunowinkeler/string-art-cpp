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

        bool Initialize(const model::Configs& configs);
        void Render();
        void Clear();
        void Destroy();

        SDL_Renderer* GetRenderer();
        SDL_Window* GetWindow();

    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
    };
}

#endif // APP_RENDERER_HPP
