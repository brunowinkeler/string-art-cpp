#include "Texture.h"
#include "Renderer.h"
#include "core/utils/LoggerConfig.hpp"
#include <SDL3_image/SDL_image.h>

namespace core
{
    Texture2D::Texture2D(const std::string& path)
        : m_Path(path)
        , m_Width(0)
        , m_Height(0)
        , m_Texture(nullptr)
    {
        SDL_Renderer* renderer = Renderer::GetNativeRenderer();
        if (!renderer)
        {
            core::utils::Logger::error("Cannot create texture: Renderer is null");
            return;
        }

        m_Texture = IMG_LoadTexture(renderer, path.c_str());
        if (!m_Texture)
        {
            core::utils::Logger::error("Failed to load texture {}: {}", path, SDL_GetError());
            return;
        }

        float w, h;
        SDL_GetTextureSize(m_Texture, &w, &h);
        m_Width = static_cast<uint32_t>(w);
        m_Height = static_cast<uint32_t>(h);
    }

    Texture2D::Texture2D(SDL_Surface* surface)
        : m_Path("From Surface")
        , m_Width(0)
        , m_Height(0)
        , m_Texture(nullptr)
    {
        if (!surface)
        {
            core::utils::Logger::error("Cannot create texture from null surface");
            return;
        }

        SDL_Renderer* renderer = Renderer::GetNativeRenderer();
        if (!renderer)
        {
            core::utils::Logger::error("Cannot create texture: Renderer is null");
            return;
        }

        m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!m_Texture)
        {
            core::utils::Logger::error("Failed to create texture from surface: {}", SDL_GetError());
            return;
        }

        m_Width = static_cast<uint32_t>(surface->w);
        m_Height = static_cast<uint32_t>(surface->h);
    }

    Texture2D::~Texture2D()
    {
        if (m_Texture)
            SDL_DestroyTexture(m_Texture);
    }
}
