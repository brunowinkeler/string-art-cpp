#ifndef IMAGING_IMAGEPROCESSOR_HPP
#define IMAGING_IMAGEPROCESSOR_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <utility>
#include <vector>

namespace imaging
{
    class ImageProcessor
    {
    public:
        ImageProcessor() = default;
        ~ImageProcessor() = default;

        std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
        convertToGrayscale(SDL_Surface* source);
        void applyCircularMask(SDL_Surface* surface, int radius);
        int getPixelBrightness(SDL_Surface* surface, int x, int y) const;
        void darkenLine(SDL_Surface* surface,
            const std::vector<std::pair<int, int>>& pixels,
            int amount = 20);

    private:
        Uint8 calculateGrayscale(Uint8 r, Uint8 g, Uint8 b) const;
    };
}

#endif // IMAGING_IMAGEPROCESSOR_HPP
