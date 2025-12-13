#include "FontManager.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace app
{
    bool FontManager::Initialize()
    {
        if (TTF_Init() != true)
        {
            core::utils::Logger::error("TTF_Init failed: {}", SDL_GetError());
            TTF_Quit();
            return false;
        }
        return true;
    }

    void FontManager::Shutdown()
    {
        for (auto& pair : m_fonts)
        {
            TTF_CloseFont(pair.second);
        }
        m_fonts.clear();
        TTF_Quit();
    }

    FontManager& FontManager::GetInstance()
    {
        static FontManager instance;
        return instance;
    }

    bool FontManager::LoadFont(const std::string& fontName, const std::string& fontPath, int fontSize)
    {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font)
        {
            return false;
        }
        m_fonts[fontName] = font;
        core::utils::Logger::info("Loaded font '{}' from '{}'", fontName, fontPath);
        return true;
    }

    void FontManager::UnloadFont(const std::string& fontName)
    {
        auto it = m_fonts.find(fontName);
        if (it != m_fonts.end())
        {
            TTF_CloseFont(it->second);
            m_fonts.erase(it);
        }
    }

    TTF_Font* FontManager::GetFont(const std::string& fontName) const
    {
        auto it = m_fonts.find(fontName);
        return (it != m_fonts.end()) ? it->second : nullptr;
    }
}
