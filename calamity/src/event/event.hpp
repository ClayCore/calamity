#pragma once

#include "zcommon.hpp"

namespace EventSystem
{
    enum class EventType : u16 {
        None = 0,
        // Window handling events
        // ======================
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        // Resource handling
        // =================
        LoadResource,
        FreeResource,

        // Engine internals related
        // ========================
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
    // ==================================
    class BaseEvent
    {
        public:
        // TODO: Test whether `this->m_type` has to be
        // a ref or a const ref or just a value.
        BaseEvent(const EventType& type) : m_type(type) {}

        // Accessor methods
        // ================
        virtual const char*
        get_name() const = 0;

        virtual EventType
        get_type() const = 0;

        virtual std::string
        to_string() const
        {
            return this->get_name();
        }

        // Overloads
        // =========
        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEvent& e)
        {
            return os << e.to_string();
        }

        private:
        // Type of the event
        // =================
        const EventType& m_type;
    };

    // Base dispatcher
    // Derive to send and release distinct events
    class BaseDispatcher
    {
        public:
        using EvPtr    = std::shared_ptr<BaseEvent>;
        using Listener = std::shared_ptr<BaseListener>;

        // TODO: Test whether this has to be const ref
        BaseDispatcher(const std::vector<EvPtr>& events) : m_events(events) {}

        // Dispatch method
        // ===============
        virtual void
        dispatch(const Listener& listener) = 0;

        // Add an event
        virtual void
        add_event(const EvPtr& event);

        // Accessor methods
        // ================
        virtual const char*
        get_event_name(usize index) const = 0;

        virtual const EventType
        get_type(usize index) const = 0;

        virtual const std::string
        to_string(usize index) const = 0;

        std::vector<EvPtr> m_events;
    };

    // Base listener
    // Derive to listen to specific events
    // ===================================
    class BaseListener
    {
        public:
        using EvPtr    = std::shared_ptr<BaseEvent>;
        using Dispatch = std::unique_ptr<BaseDispatcher>;
        using Callback = std::function<void()>;

        // Handles a distinct event
        // sent by a released dispatch
        virtual void
        on_event(const EvPtr& event);

        // Accessor and mutator methods
        // ================
        virtual void
        add_callback(const EventType& type, const Callback& cb)
        {
            this->m_callbacks.insert(std::pair<EventType, Callback>(type, cb));
        }

        virtual void
        call_func(const EventType& type)
        {
            this->m_callbacks[type]();
        }

        private:
        // List of callbacks for specific events
        std::map<EventType, Callback> m_callbacks;
    };

    // Base emitter
    // Derive to be able to emit
    // specific events, to be captured by distinct dispatchers
    // and listeners.
    // =======================================================
    class BaseEmitter
    {
        public:
        // Handy typedef
        using EvPtr   = std::shared_ptr<BaseEvent>;
        using DispPtr = std::shared_ptr<BaseDispatcher>;

        public:
        // Emits a specific event to a distinct dispatcher
        // ===============================================
        virtual void
        emit(const EvPtr& event, DispPtr& dispatcher);

        // Accessor methods
        // ================
        virtual DispPtr
        get_dispatcher()
        {
            return this->m_dispatcher;
        }

        virtual std::string
        to_string() const
        {
            std::vector<std::string> buffer;
            for (auto it = this->m_events.begin(); it < this->m_events.end(); ++it) {
                // Extract the event from the array
                EvPtr event = *it;

                // Acquire the string from the event
                std::string event_str = event->to_string().c_str();

                // Get the index of the current iteration
                // from the iterator
                usize index = static_cast<usize>(it - this->m_events.begin());

                // Start formatting into the string
                auto        format = "%u: [%s]\n";
                auto        size   = std::snprintf(nullptr, 0, format);
                std::string output(size + 1, '\0');
                std::sprintf(&output[0], format, index, event_str);

                // Add it to the vector
                buffer.push_back(output);
            }

            // Implode the buffer into a single string
            std::ostringstream implode;
            std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

            return implode.str();
        }

        // Overloads
        // =========
        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEmitter& be)
        {
            return os << be.to_string();
        }

        private:
        // Set of events to be released by this emitter
        // TODO: maybe use a vec or a map?
        // ============================================
        std::vector<EvPtr> m_events;

        // The dispatcher this emitter connects to
        // TODO: there could be multiple dispatchers
        // for a single event. Implement this later.
        // =========================================
        DispPtr m_dispatcher;
    };

} // namespace EventSystem
