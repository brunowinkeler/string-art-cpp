#include "SurfaceManager.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <SDL3_image/SDL_image.h>

namespace core
{
    std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> SurfaceManager::s_Surfaces;

    std::shared_ptr<SDL_Surface> SurfaceManager::Load(const std::string& name, const std::string& path)
    {
        if (s_Surfaces.find(name) != s_Surfaces.end())
        {
            return s_Surfaces[name];
        }

        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
        {
            core::utils::Logger::error("Failed to load surface '{}' from '{}': {}", name, path, SDL_GetError());
            return nullptr;
        }

        // Custom deleter for SDL_Surface
        std::shared_ptr<SDL_Surface> sharedSurface(surface, SDL_DestroySurface);
        s_Surfaces[name] = sharedSurface;

        core::utils::Logger::info("Loaded surface '{}' from '{}'", name, path);
        return sharedSurface;
    }

    std::shared_ptr<SDL_Surface> SurfaceManager::Get(const std::string& name)
    {
        if (s_Surfaces.find(name) != s_Surfaces.end())
        {
            return s_Surfaces[name];
        }

        core::utils::Logger::warn("Surface '{}' not found!", name);
        return nullptr;
    }

    void SurfaceManager::Unload(const std::string& name)
    {
        if (s_Surfaces.find(name) != s_Surfaces.end())
        {
            s_Surfaces.erase(name);
            core::utils::Logger::info("Unloaded surface '{}'", name);
        }
    }

    void SurfaceManager::Clear()
    {
        s_Surfaces.clear();
    }
}
