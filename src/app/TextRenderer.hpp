#ifndef APP_TEXT_RENDERER_HPP
#define APP_TEXT_RENDERER_HPP

#include <SDL3/SDL.h>
#include <string>

namespace app
{
    class TextRenderer
    {
    public:
        TextRenderer(SDL_Renderer* renderer);
        ~TextRenderer();

        void RenderText(const std::string& fontName, const std::string& text, int x, int y);

    private:
        SDL_Renderer* m_renderer;
    };
}

#endif // APP_TEXT_RENDERER_HPP
