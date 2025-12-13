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
        static FontManager& GetInstance();

        bool Initialize();
        void Shutdown();

        bool LoadFont(const std::string& fontName, const std::string& fontPath, int fontSize);
        void UnloadFont(const std::string& fontName);
        TTF_Font* GetFont(const std::string& fontName) const;

    private:
        std::unordered_map<std::string, TTF_Font*> m_fonts;
    };

}

#endif // APP_FONT_MANAGER_HPP
