#pragma once

#include "zcommon.hpp"

namespace EventSystem
{
    /* --------------------------------- **
    ** List of predefined events for use **
    ** with the derived and base classes **
    ** for event handling                **
    ** --------------------------------- */
    enum class EventType : u16 {
        None = 0,
        // Window handling events           //
        // -------------------------------- //
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        // Resource management              //
        // -------------------------------- //
        LoadResource,
        FreeResource,

        // Engine internals                 //
        // -------------------------------- //
        EngineTick,
        EngineUpdate,
        EngineRender,

        // Input handling                   //
        // -------------------------------- //
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,

        // Custom events                    //
        // -------------------------------- //
        Custom = 0xFF
    };

    /* --------------------------------- **
    ** List of categories for use with   **
    ** predefined events                 **
    ** --------------------------------- */
    enum class EventCategory : u8 {
        // Used only for initialization           //
        // -------------------------------------- //
        None = 0,

        // The following types correspond
        // to the table above.
        Window,
        Resource,
        Engine,
        Input,

        // For custom events           //
        // --------------------------- //
        Custom = 0xFF
    };

    /* ----------------------------------- **
    ** Derive this class for custom events **
    ** ----------------------------------- */
    class Event
    {
        // Constructors           //
        // ---------------------- //

        // NOTE: for predefined event types
        // use only explicit type constructors
        public:
        Event();
        Event(const EventType& type);

        virtual ~Event() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual const char*
        get_name() const;

        virtual EventType
        get_type() const;

        virtual EventCategory
        get_category() const;

        virtual const char*
        get_name_from_type(const EventType& type) const;

        virtual EventCategory
        get_category_from_type(const EventType& type) const;

        virtual void
        set_name(const std::string& name);

        // Overloads           //
        // ------------------- //
        friend inline bool
        operator==(const Event& lhs, const Event& rhs)
        {
            return lhs.get_name() == rhs.get_name();
        }

        friend inline bool
        operator!=(const Event& lhs, const Event& rhs)
        {
            return !(lhs == rhs);
        }

        // The function below is completely useless and not necessary
        // however, the compiler complains that dereferencing
        // a shared pointer to event, uses this very operator.
        friend inline bool
        operator<(const Event& lhs, const Event& rhs)
        {
            return lhs.get_type() < rhs.get_type();
        }

        // Debugging methods           //
        // --------------------------- //
        std::string
        to_string() const;

        friend inline std::ostream&
        operator<<(std::ostream& os, const Event& ev)
        {
            return os << ev.to_string();
        }

        // Bound variables           //
        // ------------------------- //
        EventType     m_type;
        EventCategory m_category;
        std::string   m_name;
    };
} // namespace EventSystem
