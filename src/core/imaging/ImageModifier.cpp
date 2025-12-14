#include "ImageModifier.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <algorithm>

namespace core
{
    namespace imaging
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
    }
}
