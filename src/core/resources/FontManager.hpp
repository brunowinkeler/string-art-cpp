#ifndef CORE_RESOURCES_FONTMANAGER_HPP
#define CORE_RESOURCES_FONTMANAGER_HPP

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace core
{
    // Responsável apenas pelo ciclo de vida da biblioteca TTF
    class FontSystem
    {
    public:
        static void Init();
        static void Shutdown();
    };

    // Responsável apenas pelo cache e acesso aos recursos de fonte
    class FontManager
    {
    public:
        static bool Load(const std::string& name, const std::string& path, int fontSize);
        static TTF_Font* Get(const std::string& name);
        static void Unload(const std::string& name);
        static void Clear();

    private:
        // Usando raw pointer aqui pois TTF_Font é opaco e gerenciado por TTF_CloseFont
        // Poderíamos usar unique_ptr com custom deleter para ser mais C++ moderno
        static std::unordered_map<std::string, TTF_Font*> s_Fonts;
    };
}

#endif // CORE_RESOURCES_FONTMANAGER_HPP
