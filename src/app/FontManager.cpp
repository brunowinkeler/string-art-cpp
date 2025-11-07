#include "FontManager.hpp"
#include "utils/LoggerConfig.hpp"

namespace app
{
    bool FontManager::initialize()
    {
        // SDL_ttf
        if (TTF_Init() != true)
        {
            utils::logger::error("TTF_Init failed: {}", SDL_GetError());
            TTF_Quit();
            return false;
        }
        return true;
    }

    void FontManager::shutdown()
    {
        for (auto& pair : m_fonts)
        {
            TTF_CloseFont(pair.second);
        }
        m_fonts.clear();
        TTF_Quit();
    }

    FontManager& FontManager::getInstance()
    {
        static FontManager instance;
        return instance;
    }

    bool FontManager::loadFont(const std::string& fontName, const std::string& fontPath, int fontSize)
    {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font)
        {
            return false;
        }
        m_fonts[fontName] = font;
        utils::logger::info("Loaded font '{}' from '{}'", fontName, fontPath);
        return true;
    }

    void FontManager::unloadFont(const std::string& fontName)
    {
        auto it = m_fonts.find(fontName);
        if (it != m_fonts.end())
        {
            TTF_CloseFont(it->second);
            m_fonts.erase(it);
        }
    }

    TTF_Font* FontManager::getFont(const std::string& fontName) const
    {
        auto it = m_fonts.find(fontName);
        return (it != m_fonts.end()) ? it->second : nullptr;
    }
}
