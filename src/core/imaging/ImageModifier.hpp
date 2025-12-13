#ifndef CORE_IMAGING_IMAGEMODIFIER_HPP
#define CORE_IMAGING_IMAGEMODIFIER_HPP

#include <SDL3/SDL.h>
#include <utility>
#include <vector>

namespace core
{
    namespace imaging
    {
        class ImageModifier
        {
        public:
            static void ApplyCircularMask(SDL_Surface* surface, int radius);
            static void DarkenLine(SDL_Surface* surface,
                const std::vector<std::pair<int, int>>& pixels,
                int amount = 20);
        };
    }
}

#endif // CORE_IMAGING_IMAGEMODIFIER_HPP
