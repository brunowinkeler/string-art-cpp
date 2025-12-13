#pragma once

#include "Texture.h"
#include <SDL3/SDL.h>
#include <memory>

namespace core
{
    class Renderer
    {
    public:
        static void Init(SDL_Renderer* renderer);
        static void Shutdown();

        static void SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        static void SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        static void Clear();
        static void Present();

        // Primitives
        static void DrawPoint(float x, float y);
        static void DrawLine(float x1, float y1, float x2, float y2);
        static void DrawRect(float x, float y, float w, float h);
        static void FillRect(float x, float y, float w, float h);

        // Images
        static void DrawTexture(const std::shared_ptr<Texture2D>& texture, float x, float y, float w, float h);
        static void DrawTexture(SDL_Texture* texture, float x, float y, float w, float h);

        static SDL_Renderer* GetNativeRenderer()
        {
            return s_Renderer;
        }

    private:
        static SDL_Renderer* s_Renderer;
    };
}
