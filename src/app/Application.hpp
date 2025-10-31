#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "SDL3/SDL.h"

namespace app
{
    class Application
    {
    public:
        Application();
        ~Application();
        void run();

    private:
        SDL_Renderer* m_renderer;
        SDL_Window* m_window;
    };
}
#endif // APP_APPLICATION_HPP
