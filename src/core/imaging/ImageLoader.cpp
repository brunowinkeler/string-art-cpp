#include "ImageLoader.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <SDL3_image/SDL_image.h>

namespace imaging
{
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
    ImageLoader::loadImage(const std::string& imagePath)
    {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        if (!surface)
        {
            utils::logger::error("Failed to load image: {}", SDL_GetError());
            return { nullptr, SDL_DestroySurface };
        }

        utils::logger::info("Image loaded: {}x{} from {}",
            surface->w, surface->h, imagePath);

        return { surface, SDL_DestroySurface };
    }
}
