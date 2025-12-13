#ifndef CORE_IMAGING_IMAGECONVERTER_HPP
#define CORE_IMAGING_IMAGECONVERTER_HPP

#include <SDL3/SDL.h>
#include <memory>

namespace core
{
    namespace imaging
    {
        class ImageConverter
        {
        public:
            static std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
            ConvertToGrayscale(SDL_Surface* source);
        };
    }
}

#endif // CORE_IMAGING_IMAGECONVERTER_HPP
