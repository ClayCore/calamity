#pragma once

#include "zcommon.hpp"

namespace EventSystem
{
    enum class EventType : u16 {
        None = 0,
        // Window handling events
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        // Engine internals related
        EngineTick,
        EngineUpdate,
        EngineRender,

        // Input handling
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    class Event
    {
      public:
        bool handled = false;

        virtual EventType
        get_event_type() const = 0;

        virtual const char*
        get_name() const
        {
            switch (this->get_event_type()) {
                    // clang-format off
                
                case EventType::None                    : return "None";
                case EventType::WindowClose             : return "WindowClose";
                case EventType::WindowResize            : return "WindowResize";
                case EventType::WindowFocus             : return "WindowFocus";
                case EventType::WindowLostFocus         : return "WindowLostFocus";
                case EventType::WindowMoved             : return "WindowMoved";
                case EventType::EngineTick              : return "EngineTick";
                case EventType::EngineUpdate            : return "EngineUpdate";
                case EventType::KeyPressed              : return "KeyPressed";
                case EventType::KeyReleased             : return "KeyReleased";
                case EventType::MouseButtonPressed      : return "MouseButtonPressed";
                case EventType::MouseButtonReleased     : return "MouseButtonReleased";
                case EventType::MouseMoved              : return "MouseMoved";
                case EventType::MouseScrolled           : return "MouseScrolled";

                    // clang-format on
            }
        }

        virtual std::string
        to_string() const
        {
            return this->get_name();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const Event& e)
        {
            return os << e.to_string();
        }

        // TODO: Create an event dispatcher class
        // ======================================
    };
} // namespace EventSystem
