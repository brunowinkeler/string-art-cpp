#ifndef CORE_EVENTS_KEYBOARDEVENTS_HPP
#define CORE_EVENTS_KEYBOARDEVENTS_HPP

#include "core/events/Event.hpp"
#include <cstdint>
#include <format>

namespace core
{
    class KeyEvent : public Event
    {
    public:
        inline uint32_t GetKeyCode() const
        {
            return m_KeyCode;
        }

    protected:
        KeyEvent(uint32_t keycode)
            : m_KeyCode(keycode)
        {}

        uint32_t m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(uint32_t keycode, bool isRepeat)
            : KeyEvent(keycode)
            , m_IsRepeat(isRepeat)
        {}

        inline bool IsRepeat() const
        {
            return m_IsRepeat;
        }

        std::string ToString() const override
        {
            return std::format("KeyPressedEvent: {} (repeat={})", m_KeyCode, m_IsRepeat);
        }

        EVENT_CLASS_TYPE(KeyPressed)
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(uint32_t keycode)
            : KeyEvent(keycode)
        {}

        std::string ToString() const override
        {
            return std::format("KeyReleasedEvent: {}", m_KeyCode);
        }

        EVENT_CLASS_TYPE(KeyReleased)
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    };
}

#endif // CORE_EVENTS_KEYBOARDEVENTS_HPP
