#ifndef CORE_EVENTS_MOUSEEVENTS_HPP
#define CORE_EVENTS_MOUSEEVENTS_HPP

#include "core/events/Event.hpp"
#include <format>

namespace core
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(double x, double y)
            : m_MouseX(x)
            , m_MouseY(y)
        {}

        inline double GetX() const
        {
            return m_MouseX;
        }

        inline double GetY() const
        {
            return m_MouseY;
        }

        std::string ToString() const override
        {
            return std::format("MouseMovedEvent: {}, {}", m_MouseX, m_MouseY);
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        double m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(double xOffset, double yOffset)
            : m_XOffset(xOffset)
            , m_YOffset(yOffset)
        {}

        inline double GetXOffset() const
        {
            return m_XOffset;
        }

        inline double GetYOffset() const
        {
            return m_YOffset;
        }

        std::string ToString() const override
        {
            return std::format("MouseScrolledEvent: {}, {}", m_XOffset, m_YOffset);
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        double m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const
        {
            return m_Button;
        }

    protected:
        MouseButtonEvent(int button)
            : m_Button(button)
        {}

        int m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            return std::format("MouseButtonPressedEvent: {}", m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            return std::format("MouseButtonReleasedEvent: {}", m_Button);
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    };
}

#endif // CORE_EVENTS_MOUSEEVENTS_HPP
