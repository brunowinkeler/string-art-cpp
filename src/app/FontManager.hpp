#ifndef APP_FONT_MANAGER_HPP
#define APP_FONT_MANAGER_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace app
{
    class FontManager
    {
    public:
        static FontManager& getInstance();

        bool loadFont(const std::string& fontName, const std::string& fontPath, int fontSize);
        void unloadFont(const std::string& fontName);
        TTF_Font* getFont(const std::string& fontName) const;

    private:
        std::unordered_map<std::string, TTF_Font*> m_fonts;
    };

} // namespace app

#endif // APP_FONT_MANAGER_HPP
