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
                return 255;
            }

            const SDL_PixelFormatDetails* formatDetails =
                SDL_GetPixelFormatDetails(surface->format);

            if (!formatDetails)
            {
                return 255;
            }

            int bpp = formatDetails->bytes_per_pixel;
            Uint8* pixelPtr = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;

            Uint32 pixel = 0;
            if (bpp == 1)
            {
                pixel = *pixelPtr;
            }
            else if (bpp == 2)
            {
                pixel = *reinterpret_cast<Uint16*>(pixelPtr);
            }
            else if (bpp == 3)
            {
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    pixel = pixelPtr[0] << 16 | pixelPtr[1] << 8 | pixelPtr[2];
                else
                    pixel = pixelPtr[0] | pixelPtr[1] << 8 | pixelPtr[2] << 16;
            }
            else if (bpp == 4)
            {
                pixel = *reinterpret_cast<Uint32*>(pixelPtr);
            }

            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, formatDetails, nullptr, &r, &g, &b, &a);

            return ColorUtils::CalculateGrayscale(r, g, b);
        }
    }
}
