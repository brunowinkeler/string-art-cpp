#ifndef IMAGING_IMAGEPROCESSOR_HPP
#define IMAGING_IMAGEPROCESSOR_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <utility>
#include <vector>

namespace imaging
{
    // Responsible for image processing and transformations
    class ImageProcessor
    {
    public:
        ImageProcessor() = default;
        ~ImageProcessor() = default;

        // Converts an image to grayscale (creates new surface)
        std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
        convertToGrayscale(SDL_Surface* source);

        // Applies a circular mask to the surface (modifies in-place)
        void applyCircularMask(SDL_Surface* surface, int radius);

        // Gets the brightness value of a pixel (0 = black, 255 = white)
        int getPixelBrightness(SDL_Surface* surface, int x, int y) const;

        // Darkens pixels along a line (used during string art generation)
        void darkenLine(SDL_Surface* surface,
            const std::vector<std::pair<int, int>>& pixels,
            int amount = 20);

    private:
        // Calculates grayscale value using perceptual luminance (ITU-R BT.601)
        // Human eye is more sensitive to green (58.7%), then red (29.9%),
        // and least to blue (11.4%)
        Uint8 calculateGrayscale(Uint8 r, Uint8 g, Uint8 b) const;
    };
}

#endif // IMAGING_IMAGEPROCESSOR_HPP
