#ifndef CORE_RESOURCES_FONTMANAGER_HPP
#define CORE_RESOURCES_FONTMANAGER_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace core
{
    class FontSystem
    {
    public:
        static void Init();
        static void Shutdown();
    };

    class FontManager
    {
    public:
        static bool Load(const std::string& name, const std::string& path, int fontSize);
        static TTF_Font* Get(const std::string& name);
        static void Unload(const std::string& name);
        static void Clear();

    private:
        static std::unordered_map<std::string, TTF_Font*> s_Fonts;
    };
}

#endif // CORE_RESOURCES_FONTMANAGER_HPP
