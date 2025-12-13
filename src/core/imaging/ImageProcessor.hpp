#ifndef IMAGING_IMAGEPROCESSOR_HPP
#define IMAGING_IMAGEPROCESSOR_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <utility>
#include <vector>

namespace core
{
    namespace imaging
    {
        class ImageProcessor
        {
        public:
            ImageProcessor() = default;
            ~ImageProcessor() = default;

            std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
            ConvertToGrayscale(SDL_Surface* source);
            void ApplyCircularMask(SDL_Surface* surface, int radius);
            int GetPixelBrightness(SDL_Surface* surface, int x, int y) const;
            void DarkenLine(SDL_Surface* surface,
                const std::vector<std::pair<int, int>>& pixels,
                int amount = 20);

        private:
            Uint8 CalculateGrayscale(Uint8 r, Uint8 g, Uint8 b) const;
        };
    }
}

#endif // IMAGING_IMAGEPROCESSOR_HPP
