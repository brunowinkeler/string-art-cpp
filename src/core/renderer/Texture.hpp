#ifndef CORE_RENDERER_TEXTURE_HPP
#define CORE_RENDERER_TEXTURE_HPP

#include <memory>
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace core
{
    class Texture2D
    {
    public:
        Texture2D(const std::string& path);
        Texture2D(SDL_Surface* surface);
        ~Texture2D();

        uint32_t GetWidth() const
        {
            return m_Width;
        }

        uint32_t GetHeight() const
        {
            return m_Height;
        }

        SDL_Texture* GetNativeTexture() const
        {
            return m_Texture;
        }

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        SDL_Texture* m_Texture;
    };
}

#endif // CORE_RENDERER_TEXTURE_HPP
