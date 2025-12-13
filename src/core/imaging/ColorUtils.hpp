#ifndef CORE_IMAGING_COLORUTILS_HPP
#define CORE_IMAGING_COLORUTILS_HPP

#include <SDL3/SDL.h>

namespace core
{
    namespace imaging
    {
        class ColorUtils
        {
        public:
            static Uint8 CalculateGrayscale(Uint8 r, Uint8 g, Uint8 b)
            {
                // Grayscale conversion using perceptual luminance (ITU-R BT.601)
                return static_cast<Uint8>(0.299 * r + 0.587 * g + 0.114 * b);
            }
        };
    }
}

#endif // CORE_IMAGING_COLORUTILS_HPP
