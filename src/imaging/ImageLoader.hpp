#ifndef IMAGING_IMAGELOADER_HPP
#define IMAGING_IMAGELOADER_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace imaging
{
    // Responsible for loading images from disk
    class ImageLoader
    {
    public:
        ImageLoader() = default;
        ~ImageLoader() = default;

        // Loads an image from the specified file path
        // Returns unique_ptr to SDL_Surface with custom deleter, or nullptr on failure
        std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
        loadImage(const std::string& imagePath);
    };
}

#endif // IMAGING_IMAGELOADER_HPP
