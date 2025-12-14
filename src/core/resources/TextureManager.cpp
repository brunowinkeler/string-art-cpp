#include "TextureManager.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace core
{
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> TextureManager::s_Textures;

    std::shared_ptr<Texture2D> TextureManager::Load(const std::string& name, const std::string& path)
    {
        if (s_Textures.find(name) != s_Textures.end())
        {
            return s_Textures[name];
        }

        auto texture = std::make_shared<Texture2D>(path);
        if (texture->GetNativeTexture())
        {
            s_Textures[name] = texture;
            core::utils::Logger::info("Texture loaded: {} ({})", name, path);
            return texture;
        }

        core::utils::Logger::error("Failed to load texture: {}", path);
        return nullptr;
    }

    std::shared_ptr<Texture2D> TextureManager::Get(const std::string& name)
    {
        if (s_Textures.find(name) != s_Textures.end())
        {
            return s_Textures[name];
        }
        core::utils::Logger::warn("Texture not found in cache: {}", name);
        return nullptr;
    }

    void TextureManager::Unload(const std::string& name)
    {
        if (s_Textures.erase(name))
        {
            core::utils::Logger::info("Texture unloaded: {}", name);
        }
    }

    void TextureManager::Clear()
    {
        s_Textures.clear();
    }
}
