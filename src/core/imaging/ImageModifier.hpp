#ifndef CORE_IMAGING_IMAGEMODIFIER_HPP
#define CORE_IMAGING_IMAGEMODIFIER_HPP

#include <SDL3/SDL.h>
#include <memory>
#include <utility>
#include <vector>

namespace core::imaging
{
    class ImageModifier
    {
    public:
        static void ApplyCircularMask(SDL_Surface* surface, int radius);
        static void DarkenLine(SDL_Surface* surface,
            const std::vector<std::pair<int, int>>& pixels,
            int amount = 20);
        static std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
        ScaleToFit(SDL_Surface* surface, int maxWidth, int maxHeight);
    };
} // namespace core::imaging

#endif // CORE_IMAGING_IMAGEMODIFIER_HPP
