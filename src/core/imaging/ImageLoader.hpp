#ifndef IMAGING_IMAGELOADER_HPP
#define IMAGING_IMAGELOADER_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace imaging
{
    class ImageLoader
    {
    public:
        ImageLoader() = default;
        ~ImageLoader() = default;

        std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> loadImage(const std::string& imagePath);
    };
}

#endif // IMAGING_IMAGELOADER_HPP
