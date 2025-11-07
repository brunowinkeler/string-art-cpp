#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "app/FontManager.hpp"
#include "app/Renderer.hpp"

namespace app
{
    class Application
    {
    public:
        Application();
        ~Application();
        void run();

    private:
        void readConfigs();
        void loadFonts();

        FontManager& m_fontManager;
        Renderer* m_renderer;
    };
}
#endif // APP_APPLICATION_HPP
