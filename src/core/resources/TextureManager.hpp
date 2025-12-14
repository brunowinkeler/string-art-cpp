#ifndef CORE_RESOURCES_TEXTUREMANAGER_HPP
#define CORE_RESOURCES_TEXTUREMANAGER_HPP

#include "core/renderer/Texture.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace core
{
    class TextureManager
    {
    public:
        // Retorna uma textura do cache ou carrega se não existir
        static std::shared_ptr<Texture2D> Load(const std::string& name, const std::string& path);

        // Retorna uma textura já carregada
        static std::shared_ptr<Texture2D> Get(const std::string& name);

        // Remove uma textura do cache
        static void Unload(const std::string& name);

        // Limpa todo o cache
        static void Clear();

    private:
        static std::unordered_map<std::string, std::shared_ptr<Texture2D>> s_Textures;
    };
}

#endif // CORE_RESOURCES_TEXTUREMANAGER_HPP
