#ifndef CORE_LAYER_HPP
#define CORE_LAYER_HPP

#include "core/events/Event.hpp"

namespace core
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer")
            : m_DebugName(name)
        {}

        virtual ~Layer() = default;

        virtual void OnAttach()
        {}

        virtual void OnDetach()
        {}

        virtual void OnUpdate(float /*ts*/)
        {}

        virtual void OnRender()
        {}

        virtual void OnEvent(Event& /*event*/)
        {}

        const std::string& GetName() const
        {
            return m_DebugName;
        }

    protected:
        std::string m_DebugName;
    };
}

#endif // CORE_LAYER_HPP
