#include "ImageAnalyzer.hpp"
#include "ColorUtils.hpp"

namespace core
{
    namespace imaging
    {
        int ImageAnalyzer::GetPixelBrightness(SDL_Surface* surface, int x, int y)
        {
            if (!surface || x < 0 || y < 0 || x >= surface->w || y >= surface->h)
            {
                return 255; // White for out-of-bounds pixels
            }

            Uint32* pixels = static_cast<Uint32*>(surface->pixels);
            Uint32 pixel = pixels[y * surface->w + x];

            const SDL_PixelFormatDetails* formatDetails =
                SDL_GetPixelFormatDetails(surface->format);

            if (!formatDetails)
            {
                return 255;
            }

            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, formatDetails, nullptr, &r, &g, &b, &a);

            return ColorUtils::CalculateGrayscale(r, g, b);
        }
    }
}
