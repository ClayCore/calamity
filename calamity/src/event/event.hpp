#pragma once

#include "zcommon.hpp"

namespace EventSystem
{
    // List of predefined internal events
    // ==================================
    enum class EventType : u16 {
        None = 0,
        // Window handling events
        // ======================
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        // Resource management
        // =================
        LoadResource,
        FreeResource,

        // Engine internals
        // ================
        EngineTick,
        EngineUpdate,
        EngineRender,

        // Input handling
        // ==============
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    // Base event class
    // Derive for specialized events
    // =============================
    class BaseEvent
    {
        // Constructors
        // ============

        // NOTE: It's worth pointing out
        // that to use a predefined event type
        // the event has to be derived
        // and constructed with the type info
        // ===================================

        public:
        BaseEvent() : m_type(EventType::None) {}
        BaseEvent(const EventType& type) : m_type(type) {}
        BaseEvent(std::string& name) : m_type(EventType::None), m_name(name) {}
        BaseEvent(const char* name) : m_type(EventType::None)
        {
            this->m_name = std::string(name);
        }

        private:
        // Accessor and mutator methods
        // ============================
        virtual const char*
        get_name() const
        {
            if (!this->m_name.empty()) {
                return this->m_name.c_str();
            } else {
                return this->get_name_from_type();
            }
        };

        virtual EventType
        get_type() const
        {
            return this->m_type;
        };

        virtual void
        set_name(const std::string& name)
        {
            this->m_name = name;
        }

        // Retrieves name from the predefined types
        const char*
        get_name_from_type() const
        {
            // clang-format off
            switch (this->m_type) {
                case EventType::None:                   { return "None"; };
                // Window handling events
                // =======================================================================
                case EventType::WindowClose:            { return "WindowClose";         };
                case EventType::WindowResize:           { return "WindowResize";        };
                case EventType::WindowFocus:            { return "WindowFocus";         };
                case EventType::WindowLostFocus:        { return "WindowLostFocus";     };
                case EventType::WindowMoved:            { return "WindowMoved";         };
                // Resource management
                // =======================================================================
                case EventType::LoadResource:           { return "LoadResource";        };
                case EventType::FreeResource:           { return "FreeResource";        };
                // Engine internals
                // =======================================================================
                case EventType::EngineTick:             { return "EngineTick";          };
                case EventType::EngineUpdate:           { return "EngineUpdate";        };
                case EventType::EngineRender:           { return "EngineRender";        };
                // Input handling
                // =======================================================================
                case EventType::KeyPressed:             { return "KeyPressed";          };
                case EventType::KeyReleased:            { return "KeyReleased";         };
                case EventType::MouseButtonPressed:     { return "MouseButtonPressed";  };
                case EventType::MouseButtonReleased:    { return "MouseButtonReleased"; };
                case EventType::MouseMoved:             { return "MouseMoved";          };
                case EventType::MouseScrolled:          { return "MouseScrolled";       };
                // Unimplemented
                // =======================================================================
                default:                                { return "Unknown event";       };
            }
            // clang-format on
        }

        // Methods for debugging
        // =====================
        public:
        std::string
        to_string() const
        {
            if (!this->m_name.empty())
                return this->get_name();
            else
                return this->get_name_from_type();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEvent& e)
        {
            return os << e.to_string();
        }

        // Bound methods and variables
        // ===========================
        private:
        const EventType& m_type;
        std::string      m_name;
    };

    // Base emitter
    // Sends events to distinct dispatchers
    // ====================================
    class BaseEmitter
    {
        // Utility typedefs
        // ================
        using Event      = std::shared_ptr<BaseEvent>;
        using Dispatcher = std::shared_ptr<BaseDispatcher>;

        // Constructors
        // ============
        public:
        BaseEmitter() : m_dispatcher(std::make_shared<BaseDispatcher>()) {}
        BaseEmitter(Dispatcher& dispatcher) : m_dispatcher(dispatcher) {}
        BaseEmitter(const std::vector<Event>& events) : m_dispatcher(std::make_shared<BaseDispatcher>())
        {
            this->m_events = events;
        }

        // Accessor and mutator methods
        // ============================
        private:
        virtual void
        add_event(const Event& event)
        {
            this->m_events.push_back(event);
        }

        virtual Event
        get_event(usize index) const
        {
            if (index >= 0 && index < this->m_events.size()) {
                return this->m_events[index];
            }
        }

        virtual void
        set_event(usize index, const Event& event)
        {
            if (index >= 0 && index < this->m_events.size()) {
                auto it = index + this->m_events.begin();

                this->m_events.insert(it, event);
            }
        }

        // Emitter functions
        // =================

        // Used for emitting an event
        // using the bound dispatcher
        virtual void
        emit(const Event& event)
        {
            this->m_dispatcher->add_event(event);
        }

        // Used for emitting an event
        // -without- a bound dispatcher
        virtual void
        emit(const Event& event, const Dispatcher& dispatcher)
        {
            dispatcher->add_event(event);
        }

        // Allows us to bind
        // a distinct dispatcher
        // to our emitter object
        virtual void
        bind(const Dispatcher& dispatcher)
        {
            this->m_dispatcher = dispatcher;
        }

        // Methods for debugging
        // =====================

        // Bound methods and variables
        // ===========================
        private:
        Dispatcher         m_dispatcher;
        std::vector<Event> m_events;
    };

    // Base dispatcher
    // Captures, buffers and releases events
    // to distinct listeners
    // =====================================
    class BaseDispatcher
    {
        // Utility typedefs
        // ================
        using Event = std::shared_ptr<BaseEvent>;
        // using Listener = std::shared_ptr<BaseListener>;

        // Constructors
        // ============
        public:
        // Accessor and mutator methods
        // ============================
        private:
        // Dispatcher functions
        // ====================

        // Release a buffered event
        // through a bound listener
        virtual void
        dispatch(const Event& event);

        // Release an event to
        // a specific listener
        virtual void
        dispatch(const Event& event);

        // Methods for debugging
        // =====================
        public:
        // Bound methods and variables
        // ===========================
        private:
    };
} // namespace EventSystem
