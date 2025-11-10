#include "ImageProcessor.hpp"
#include "utils/LoggerConfig.hpp"
#include <algorithm>
#include <cmath>

namespace imaging
{
    Uint8 ImageProcessor::calculateGrayscale(Uint8 r, Uint8 g, Uint8 b) const
    {
        // Grayscale conversion using perceptual luminance (ITU-R BT.601)
        return static_cast<Uint8>(0.299 * r + 0.587 * g + 0.114 * b);
    }

    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>
    ImageProcessor::convertToGrayscale(SDL_Surface* source)
    {
        if (!source)
        {
            utils::logger::error("Cannot convert null surface to grayscale");
            return { nullptr, SDL_DestroySurface };
        }

        // Create a copy of the surface
        SDL_Surface* graySurface = SDL_ConvertSurface(source, source->format);
        if (!graySurface)
        {
            utils::logger::error("Failed to create grayscale surface: {}", SDL_GetError());
            return { nullptr, SDL_DestroySurface };
        }

        if (SDL_LockSurface(graySurface) != 0)
        {
            utils::logger::error("Failed to lock surface: {}", SDL_GetError());
            SDL_DestroySurface(graySurface);
            return { nullptr, SDL_DestroySurface };
        }

        Uint32* pixels = static_cast<Uint32*>(graySurface->pixels);
        int pixelCount = graySurface->w * graySurface->h;

        // SDL3: Use SDL_GetPixelFormatDetails to get format information
        const SDL_PixelFormatDetails* formatDetails =
            SDL_GetPixelFormatDetails(graySurface->format);

        if (!formatDetails)
        {
            utils::logger::error("Failed to get pixel format details: {}", SDL_GetError());
            SDL_UnlockSurface(graySurface);
            SDL_DestroySurface(graySurface);
            return { nullptr, SDL_DestroySurface };
        }

        for (int i = 0; i < pixelCount; i++)
        {
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixels[i], formatDetails, nullptr, &r, &g, &b, &a);

            Uint8 gray = calculateGrayscale(r, g, b);

            pixels[i] = SDL_MapRGBA(formatDetails, nullptr, gray, gray, gray, a);
        }

        SDL_UnlockSurface(graySurface);
        utils::logger::info("Image converted to grayscale");

        return { graySurface, SDL_DestroySurface };
    }

    void ImageProcessor::applyCircularMask(SDL_Surface* surface, int radius)
    {
        if (!surface)
        {
            utils::logger::error("Cannot apply mask to null surface");
            return;
        }

        if (SDL_LockSurface(surface) != 0)
        {
            utils::logger::error("Failed to lock surface: {}", SDL_GetError());
            return;
        }

        int centerX = surface->w / 2;
        int centerY = surface->h / 2;
        Uint32* pixels = static_cast<Uint32*>(surface->pixels);

        const SDL_PixelFormatDetails* formatDetails =
            SDL_GetPixelFormatDetails(surface->format);

        if (!formatDetails)
        {
            utils::logger::error("Failed to get pixel format details: {}", SDL_GetError());
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
                    // Pixel outside circle: set to white
                    pixels[y * surface->w + x] =
                        SDL_MapRGBA(formatDetails, nullptr, 255, 255, 255, 255);
                }
            }
        }

        SDL_UnlockSurface(surface);
        utils::logger::info("Circular mask applied with radius: {}", radius);
    }

    int ImageProcessor::getPixelBrightness(SDL_Surface* surface, int x, int y) const
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

        return calculateGrayscale(r, g, b);
    }

    void ImageProcessor::darkenLine(SDL_Surface* surface,
        const std::vector<std::pair<int, int>>& pixels,
        int amount)
    {
        if (!surface || pixels.empty())
        {
            return;
        }

        if (SDL_LockSurface(surface) != 0)
        {
            utils::logger::error("Failed to lock surface for darkening: {}", SDL_GetError());
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

            // Darken by subtracting value (prevent negative values)
            r = std::max(0, r - amount);
            g = std::max(0, g - amount);
            b = std::max(0, b - amount);

            surfacePixels[index] = SDL_MapRGBA(formatDetails, nullptr, r, g, b, a);
        }

        SDL_UnlockSurface(surface);
    }
}
