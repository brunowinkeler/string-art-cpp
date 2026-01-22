#ifndef STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP
#define STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP

#include "app/algorithm/StringArtGenerator.hpp"
#include "app/model/Configs.hpp"
#include "core/Layer.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/renderer/Texture.hpp"
#include <memory>

namespace app
{
    class AppLayer : public core::Layer
    {
    public:
        AppLayer();
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float ts) override;
        void OnRender() override;
        void OnEvent(core::Event& event) override;

    private:
        void LoadConfigs();
        void LoadResources();
        void InitializeGenerator();
        void RenderStringArt();
        void RenderNails();

        model::Configs m_Configs;
        algorithm::StringArtGenerator m_Generator;
        std::shared_ptr<SDL_Surface> m_SourceSurface;

        float m_OffsetX = 0.0f;
        float m_OffsetY = 0.0f;
    };
} // namespace app

#endif // STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP
