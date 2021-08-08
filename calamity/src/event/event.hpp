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
                case EventType::None:                   { return "None";                };
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
        std::string
        to_string() const
        {
            if (!this->m_name.empty())
                return this->get_name();
            else
                return this->get_name_from_type();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEvent& ev)
        {
            return os << ev.to_string();
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
        BaseEmitter()
        {
            this->m_dispatcher = std::make_shared<BaseDispatcher>();
        }

        BaseEmitter(Dispatcher& dispatcher)
        {
            this->m_dispatcher = dispatcher;
        }

        BaseEmitter(const std::vector<Event>& events)
        {
            this->m_dispatcher = std::make_shared<BaseDispatcher>();
            this->m_events     = events;
        }

        // Accessor and mutator methods
        // ============================
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

        virtual Dispatcher
        get_dispatcher() const
        {
            return this->m_dispatcher;
        }

        // Emitter functions
        // =================

        // Used for emitting an event
        // using the bound dispatcher
        virtual void
        emit(const Event& event)
        {
            this->m_dispatcher->dispatch(event);
        }

        // Used for emitting an event
        // -without- a bound dispatcher
        virtual void
        emit(const Event& event, const Dispatcher& dispatcher)
        {
            dispatcher->dispatch(event);
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
        std::string
        to_string() const
        {
            std::vector<std::string> buffer;

            buffer.push_back("Emitter: \n");

            for (auto it = this->m_events.begin(); it < this->m_events.end(); ++it) {
                // Extract the event
                Event event = *it;

                // Acquire the name
                std::string event_name = event->to_string();

                // Get the index of the current iterator
                usize index = std::distance(this->m_events.begin(), it);

                // Format into a string
                auto format = "\tEventID: %u -- [%s]\n";
                auto size   = std::snprintf(nullptr, 0, format);

                std::string output(size + 1, '\0');
                std::sprintf(&output[0], format, index, event_name.c_str());

                buffer.push_back(output);
            }

            // Implode the buffer into a single string
            std::ostringstream implode;
            std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

            return implode.str();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEmitter& em)
        {
            return os << em.to_string();
        }

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
        using Event    = std::shared_ptr<BaseEvent>;
        using Listener = std::shared_ptr<BaseListener>;

        // Constructors
        // ============
        public:
        BaseDispatcher()
        {
            this->m_listener = std::make_shared<BaseListener>();
        }

        BaseDispatcher(Listener& listener)
        {
            this->m_listener = listener;
        }

        BaseDispatcher(const std::vector<Event>& events)
        {
            this->m_listener = std::make_shared<BaseListener>();
            this->m_events   = events;
        }

        // Accessor and mutator methods
        // ============================

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

        // Dispatcher functions
        // ====================

        // Release a buffered event
        // through a bound listener
        virtual void
        dispatch(const Event& event)
        {
            m_listener->on_event(event);
        }

        // Release an event to
        // a specific listener
        virtual void
        dispatch(const Event& event, const Listener& listener)
        {
            listener->on_event(event);
        }

        // Binds a distinct listener
        // to this dispatcher object
        virtual void
        bind(const Listener& listener)
        {
            this->m_listener = listener;
        }

        // Methods for debugging
        // =====================
        std::string
        to_string() const
        {
            std::vector<std::string> buffer;

            buffer.push_back("Dispatcher: \n");

            for (auto it = this->m_events.begin(); it < this->m_events.end(); ++it) {
                Event event = *it;

                std::string event_name = event->to_string();

                usize index = std::distance(this->m_events.begin(), it);

                auto format = "\tEventID: %u -- [%s]\n";
                auto size   = std::snprintf(nullptr, 0, format);

                std::string output(size + 1, '\0');
                std::sprintf(&output[0], format, index, event_name.c_str());

                buffer.push_back(output);
            }

            std::ostringstream implode;
            std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

            return implode.str();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseDispatcher& ds)
        {
            return os << ds.to_string();
        }

        // Bound methods and variables
        // ===========================
        private:
        Listener m_listener;
        // TODO: make this a buffered queue or something
        std::vector<Event> m_events;
    };

    // Base listener
    // Calls a callback functor
    // based on the event
    class BaseListener
    {
        // Utility typedefs
        // ================
        using Event      = std::shared_ptr<BaseEvent>;
        using Dispatcher = std::shared_ptr<BaseDispatcher>;
        using Callback   = std::function<void()>;

        // Constructors
        // ============
        public:
        BaseListener()
        {
            this->m_dispatcher = std::make_shared<BaseDispatcher>();
        }

        BaseListener(Dispatcher& dispatcher)
        {
            this->m_dispatcher = dispatcher;
        }

        BaseListener(const std::map<Event, Callback>& actions)
        {
            this->m_dispatcher = std::make_shared<BaseDispatcher>();
            this->m_actions    = actions;
        }
        // Accessor and mutator methods
        // ============================

        // Insert an event and a callback function
        // that maps to it
        virtual void
        insert_event(const Event& event, const Callback& cb)
        {
            this->m_actions.emplace(event, cb);
        }

        // Sets or updates a callback functor
        // for a given event
        virtual void
        set_callback(const Event& event, const Callback& cb)
        {
            this->m_actions[event] = cb;
        }

        // Acquire a callback functor
        // based on the event structure
        virtual Callback
        get_callback(const Event& event)
        {
            return this->m_actions[event];
        }

        // Alternatively acquire it based
        // on type or name
        virtual Callback
        get_callback(const std::string& name)
        {
            for (auto&& [event, callback] : this->m_actions) {
                if (event->get_name() == name) {
                    return callback;
                }
            }
        }

        // Listener functions
        // ==================

        // Handles an event
        // sent by a bound dispatcher
        // NOTE: Must be overriden
        virtual void
        on_event(const Event& event) = 0;

        // Handles an event
        // sent by an external dispatcher
        // NOTE: Must be overriden
        virtual void
        on_event(const Event& event, const Dispatcher& dispatcher) = 0;

        // Methods for debugging
        // =====================
        std::string
        to_string() const
        {
            std::vector<std::string> buffer;

            buffer.push_back("Listener: \n");

            for (auto it = this->m_actions.begin(); it != this->m_actions.end(); ++it) {
                Event event = it->first;

                std::string event_name = event->to_string();

                usize index = std::distance(this->m_actions.begin(), it);

                auto format = "\tEventID: %u -- [%s]\n";
                auto size   = std::snprintf(nullptr, 0, format);

                std::string output(size + 1, '\0');
                std::sprintf(&output[0], format, index, event_name.c_str());

                buffer.push_back(output);
            }

            std::ostringstream implode;
            std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

            return implode.str();
        }

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseListener& ls)
        {
            return os << ls.to_string();
        }

        // Bound methods and variables
        // ===========================
        private:
        Dispatcher m_dispatcher;

        std::map<Event, Callback> m_actions;
    };
} // namespace EventSystem
