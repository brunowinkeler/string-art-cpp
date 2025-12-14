#include "Application.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/resources/FontManager.hpp"
#include "core/resources/SurfaceManager.hpp"
#include "core/resources/TextureManager.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <ranges>

namespace core
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& spec)
        : m_Specification(spec)
    {
        s_Instance = this;

        // Initialize Systems
        FontSystem::Init();

        // Setup Window Specification
        m_Specification.WindowSpec.Title = spec.Name;
        m_Specification.WindowSpec.EventCallback = [this](Event& e)
        {
            GenericEventCallback(e);
        };

        m_Window = std::make_unique<Window>(m_Specification.WindowSpec);
        m_Window->Create();

        Renderer::Init(m_Window->GetRenderer());
    }

    Application::~Application()
    {
        for (auto& layer : m_LayerStack)
        {
            layer->OnDetach();
        }
        m_LayerStack.clear();

        // Shutdown Systems
        SurfaceManager::Clear();
        TextureManager::Clear();
        FontManager::Clear();
        FontSystem::Shutdown();
        Renderer::Shutdown();

        m_Window->Destroy();
    }

    void Application::Run()
    {
        m_Running = true;
        float lastFrameTime = SDL_GetTicks() / 1000.0f;

        while (m_Running)
        {
            // Poll events
            m_Window->Update();

            if (m_Window->ShouldClose())
            {
                Stop();
                break;
            }

            float time = SDL_GetTicks() / 1000.0f;
            float timestep = time - lastFrameTime;
            lastFrameTime = time;

            // Update layers
            for (const auto& layer : m_LayerStack)
                layer->OnUpdate(timestep);

            Renderer::Clear();

            // Render layers
            for (const auto& layer : m_LayerStack)
                layer->OnRender();

            Renderer::Present();
        }
    }

    void Application::Stop()
    {
        m_Running = false;
    }

    void Application::GenericEventCallback(Event& event)
    {
        for (auto& layer : std::views::reverse(m_LayerStack))
        {
            layer->OnEvent(event);
            if (event.Handled)
                break;
        }
    }
}
