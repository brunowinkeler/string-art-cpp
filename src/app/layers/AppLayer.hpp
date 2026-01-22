#ifndef STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP
#define STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP

#include "core/Layer.hpp"
#include "core/imaging/ImageConverter.hpp"
#include "core/imaging/ImageModifier.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/resources/FontManager.hpp"
#include "core/resources/SurfaceManager.hpp"
#include "core/utils/LoggerConfig.hpp"

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

    private:
        void LoadResources();
        void ResetSimulationState();
        void OnEvent(core::Event& event) override;
        std::shared_ptr<core::Texture2D> m_ProcessedTexture;
    };
} // namespace app

#endif // STRING_ART_CPP_APP_LAYERS_APPLAYER_HPP
