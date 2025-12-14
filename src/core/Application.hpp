#pragma once

#include "core/Layer.hpp"
#include "core/Window.hpp"
#include "core/events/Event.hpp"
#include "core/events/WindowEvents.hpp"
#include <concepts>
#include <memory>
#include <string>
#include <vector>

namespace core
{
    struct ApplicationSpecification
    {
        std::string Name = "String Art App";
        WindowSpecification WindowSpec;
    };

    class Application
    {
    public:
        Application(const ApplicationSpecification& spec);
        virtual ~Application();

        void Run();
        void Stop();

        void GenericEventCallback(Event& event);

        template<typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
        void PushLayer()
        {
            m_LayerStack.emplace_back(std::make_unique<TLayer>());
            m_LayerStack.back()->OnAttach();
        }

        Window& GetWindow()
        {
            return *m_Window;
        }

        static Application& Get()
        {
            return *s_Instance;
        }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

    private:
        ApplicationSpecification m_Specification;
        std::unique_ptr<Window> m_Window;
        bool m_Running = false;

        std::vector<std::unique_ptr<Layer>> m_LayerStack;

        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication(int argc, char** argv);
}
