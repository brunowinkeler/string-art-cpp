#ifndef CORE_RESOURCES_SURFACEMANAGER_HPP
#define CORE_RESOURCES_SURFACEMANAGER_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace core
{
    class SurfaceManager
    {
    public:
        static std::shared_ptr<SDL_Surface> Load(const std::string& name, const std::string& path);
        static std::shared_ptr<SDL_Surface> Get(const std::string& name);
        static void Unload(const std::string& name);
        static void Clear();

    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> s_Surfaces;
    };
}

#endif // CORE_RESOURCES_SURFACEMANAGER_HPP
