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
        void UpdateLayout();

        void RenderSourceCircle();
        void RenderReconstructedCircle();
        void RenderNails(float offsetX, float offsetY);

        model::Configs m_Configs;
        algorithm::StringArtGenerator m_Generator;
        std::shared_ptr<SDL_Surface> m_SourceSurface;
        std::shared_ptr<core::Texture2D> m_WorkingTexture;
        SDL_Texture* m_SourceTexture = nullptr;

        float m_Zoom = 1.0f;
        float m_LeftOffsetX = 0.0f;
        float m_LeftOffsetY = 0.0f;
        float m_RightOffsetX = 0.0f;
        float m_RightOffsetY = 0.0f;
        int m_CircleRadius = 0;
    };
} // namespace app

#endif // STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP
