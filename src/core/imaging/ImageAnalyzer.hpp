#ifndef CORE_IMAGING_IMAGEANALYZER_HPP
#define CORE_IMAGING_IMAGEANALYZER_HPP

#include <SDL3/SDL.h>

namespace core
{
    namespace imaging
    {
        class ImageAnalyzer
        {
        public:
            static int GetPixelBrightness(SDL_Surface* surface, int x, int y);
        };
    }
}

#endif // CORE_IMAGING_IMAGEANALYZER_HPP
