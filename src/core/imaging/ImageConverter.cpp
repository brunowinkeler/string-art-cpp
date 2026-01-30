#include "ImageConverter.hpp"
#include "ColorUtils.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace core::imaging
{
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
    ImageConverter::ConvertToGrayscale(SDL_Surface* source)
    {
        if (!source)
        {
            core::utils::Logger::error("Cannot convert null surface to grayscale");
            return { nullptr, SDL_DestroySurface };
        }

        SDL_Surface* graySurface = SDL_ConvertSurface(source, source->format);
        if (!graySurface)
        {
            core::utils::Logger::error("Failed to create grayscale surface: {}", SDL_GetError());
            return { nullptr, SDL_DestroySurface };
        }

        if (SDL_LockSurface(graySurface) != true)
        {
            core::utils::Logger::error("Failed to lock surface: {}", SDL_GetError());
            SDL_DestroySurface(graySurface);
            return { nullptr, SDL_DestroySurface };
        }

        Uint32* pixels = static_cast<Uint32*>(graySurface->pixels);
        int pixelCount = graySurface->w * graySurface->h;

        const SDL_PixelFormatDetails* formatDetails =
            SDL_GetPixelFormatDetails(graySurface->format);

        if (!formatDetails)
        {
            core::utils::Logger::error("Failed to get pixel format details: {}", SDL_GetError());
            SDL_UnlockSurface(graySurface);
            SDL_DestroySurface(graySurface);
            return { nullptr, SDL_DestroySurface };
        }

        for (int i = 0; i < pixelCount; i++)
        {
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixels[i], formatDetails, nullptr, &r, &g, &b, &a);

            Uint8 gray = ColorUtils::CalculateGrayscale(r, g, b);

            pixels[i] = SDL_MapRGBA(formatDetails, nullptr, gray, gray, gray, a);
        }

        SDL_UnlockSurface(graySurface);
        core::utils::Logger::info("Image converted to grayscale");

        return { graySurface, SDL_DestroySurface };
    }
}
