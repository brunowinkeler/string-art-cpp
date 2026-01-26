#include "Renderer.hpp"

namespace core
{
    SDL_Renderer* Renderer::s_Renderer = nullptr;

    void Renderer::Init(SDL_Renderer* renderer)
    {
        s_Renderer = renderer;
    }

    void Renderer::Shutdown()
    {
        s_Renderer = nullptr;
    }

    void Renderer::SetDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        if (s_Renderer)
            SDL_SetRenderDrawColor(s_Renderer, r, g, b, a);
    }

    void Renderer::Clear()
    {
        if (s_Renderer)
            SDL_RenderClear(s_Renderer);
    }

    void Renderer::Present()
    {
        if (s_Renderer)
            SDL_RenderPresent(s_Renderer);
    }

    void Renderer::DrawPoint(float x, float y)
    {
        if (s_Renderer)
            SDL_RenderPoint(s_Renderer, x, y);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        if (s_Renderer)
            SDL_RenderLine(s_Renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawRect(float x, float y, float w, float h)
    {
        if (s_Renderer)
        {
            SDL_FRect rect = { x, y, w, h };
            SDL_RenderRect(s_Renderer, &rect);
        }
    }

    void Renderer::FillRect(float x, float y, float w, float h)
    {
        if (s_Renderer)
        {
            SDL_FRect rect = { x, y, w, h };
            SDL_RenderFillRect(s_Renderer, &rect);
        }
    }

    void Renderer::DrawTexture(SDL_Texture* texture, float x, float y, float w, float h)
    {
        if (s_Renderer && texture)
        {
            SDL_FRect dstRect = { x, y, w, h };
            SDL_RenderTexture(s_Renderer, texture, nullptr, &dstRect);
        }
    }

    void Renderer::DrawTexture(const std::shared_ptr<Texture2D>& texture, float x, float y, float w, float h)
    {
        if (texture)
            DrawTexture(texture->GetNativeTexture(), x, y, w, h);
    }
}
