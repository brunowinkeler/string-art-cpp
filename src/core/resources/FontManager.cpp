#include "FontManager.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace core
{
    // --- FontSystem ---

    void FontSystem::Init()
    {
        if (TTF_Init() != true)
        {
            core::utils::Logger::error("TTF_Init failed: {}", SDL_GetError());
        }
        else
        {
            core::utils::Logger::info("FontSystem Initialized");
        }
    }

    void FontSystem::Shutdown()
    {
        TTF_Quit();
        core::utils::Logger::info("FontSystem Shutdown");
    }

    // --- FontManager ---

    std::unordered_map<std::string, TTF_Font*> FontManager::s_Fonts;

    bool FontManager::Load(const std::string& name, const std::string& path, int fontSize)
    {
        if (s_Fonts.find(name) != s_Fonts.end())
        {
            core::utils::Logger::warn("Font already loaded: {}", name);
            return true;
        }

        TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
        if (!font)
        {
            core::utils::Logger::error("Failed to load font '{}': {}", path, SDL_GetError());
            return false;
        }

        s_Fonts[name] = font;
        core::utils::Logger::info("Font loaded: {} ({})", name, path);
        return true;
    }

    TTF_Font* FontManager::Get(const std::string& name)
    {
        if (s_Fonts.find(name) != s_Fonts.end())
        {
            return s_Fonts[name];
        }
        core::utils::Logger::error("Font not found: {}", name);
        return nullptr;
    }

    void FontManager::Unload(const std::string& name)
    {
        auto it = s_Fonts.find(name);
        if (it != s_Fonts.end())
        {
            TTF_CloseFont(it->second);
            s_Fonts.erase(it);
            core::utils::Logger::info("Font unloaded: {}", name);
        }
    }

    void FontManager::Clear()
    {
        for (auto& pair : s_Fonts)
        {
            TTF_CloseFont(pair.second);
        }
        s_Fonts.clear();
    }
}
