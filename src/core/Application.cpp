#include "Application.h"
#include "core/utils/LoggerConfig.hpp"

namespace core
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& spec)
        : m_Specification(spec)
    {
        s_Instance = this;

        // Setup Window Specification
        m_Specification.WindowSpec.Title = spec.Name;
        m_Specification.WindowSpec.EventCallback = [this](Event& e)
        {
            OnEvent(e);
        };

        m_Window = std::make_unique<Window>(m_Specification.WindowSpec);
        m_Window->Create();
    }

    Application::~Application()
    {
        for (auto& layer : m_LayerStack)
        {
            layer->OnDetach();
        }
        m_LayerStack.clear();

        m_Window->Destroy();
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = 0.0f;
            float timestep = time;

            if (m_Window->ShouldClose())
                m_Running = false;

            for (auto& layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_Window->Update();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)
            {
                return OnWindowClose(e);
            });

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
