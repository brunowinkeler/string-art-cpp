#include "ImageModifier.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <algorithm>

namespace core::imaging
{
    void ImageModifier::ApplyCircularMask(SDL_Surface* surface, int radius)
    {
        if (!surface)
        {
            core::utils::Logger::error("Cannot apply mask to null surface");
            return;
        }

        if (SDL_LockSurface(surface) != true)
        {
            core::utils::Logger::error("Failed to lock surface: {}", SDL_GetError());
            return;
        }

        int centerX = surface->w / 2;
        int centerY = surface->h / 2;
        Uint32* pixels = static_cast<Uint32*>(surface->pixels);

        const SDL_PixelFormatDetails* formatDetails =
            SDL_GetPixelFormatDetails(surface->format);

        if (!formatDetails)
        {
            core::utils::Logger::error("Failed to get pixel format details: {}", SDL_GetError());
            SDL_UnlockSurface(surface);
            return;
        }

        for (int y = 0; y < surface->h; y++)
        {
            for (int x = 0; x < surface->w; x++)
            {
                int dx = x - centerX;
                int dy = y - centerY;
                int distSquared = dx * dx + dy * dy;

                if (distSquared > radius * radius)
                {
                    pixels[y * surface->w + x] =
                        SDL_MapRGBA(formatDetails, nullptr, 255, 255, 255, 255);
                }
            }
        }

        SDL_UnlockSurface(surface);
        core::utils::Logger::info("Circular mask applied with radius: {}", radius);
    }

    void ImageModifier::DarkenLine(SDL_Surface* surface,
        const std::vector<std::pair<int, int>>& pixels,
        int amount)
    {
        if (!surface || pixels.empty())
        {
            return;
        }

        if (SDL_LockSurface(surface) != true)
        {
            core::utils::Logger::error("Failed to lock surface for darkening: {}", SDL_GetError());
            return;
        }

        Uint32* surfacePixels = static_cast<Uint32*>(surface->pixels);
        const SDL_PixelFormatDetails* formatDetails =
            SDL_GetPixelFormatDetails(surface->format);

        if (!formatDetails)
        {
            SDL_UnlockSurface(surface);
            return;
        }

        for (const auto& [x, y] : pixels)
        {
            if (x < 0 || y < 0 || x >= surface->w || y >= surface->h)
                continue;

            int index = y * surface->w + x;
            Uint32 pixel = surfacePixels[index];

            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, formatDetails, nullptr, &r, &g, &b, &a);

            r = std::max(0, r - amount);
            g = std::max(0, g - amount);
            b = std::max(0, b - amount);

            surfacePixels[index] = SDL_MapRGBA(formatDetails, nullptr, r, g, b, a);
        }

        SDL_UnlockSurface(surface);
    }

    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
    ImageModifier::ScaleToFit(SDL_Surface* surface, int maxWidth, int maxHeight)
    {
        if (!surface)
        {
            return { nullptr, SDL_DestroySurface };
        }

        float scaleX = static_cast<float>(maxWidth) / surface->w;
        float scaleY = static_cast<float>(maxHeight) / surface->h;
        float scale = std::min(scaleX, scaleY);

        if (scale >= 1.0f)
        {
            SDL_Surface* copy = SDL_ConvertSurface(surface, surface->format);
            return { copy, SDL_DestroySurface };
        }

        int newWidth = static_cast<int>(surface->w * scale);
        int newHeight = static_cast<int>(surface->h * scale);

        SDL_Surface* scaled = SDL_CreateSurface(newWidth, newHeight, surface->format);
        if (!scaled)
        {
            core::utils::Logger::error("Failed to create scaled surface: {}", SDL_GetError());
            return { nullptr, SDL_DestroySurface };
        }

        if (!SDL_BlitSurfaceScaled(surface, nullptr, scaled, nullptr, SDL_SCALEMODE_LINEAR))
        {
            core::utils::Logger::error("Failed to scale surface: {}", SDL_GetError());
            SDL_DestroySurface(scaled);
            return { nullptr, SDL_DestroySurface };
        }

        core::utils::Logger::info("Image scaled from {}x{} to {}x{}",
            surface->w, surface->h, newWidth, newHeight);

        return { scaled, SDL_DestroySurface };
    }
}
