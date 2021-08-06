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
    };

    // Base listener
    // Derive to listen to specific events
    // ===================================
    class BaseListener
    {
        private:
        using EvPtr    = std::unique_ptr<BaseEvent>;
        using Dispatch = std::unique_ptr<BaseDispatcher>;
        using Callback = std::function<void()>;

        public:
        // Handles a distinct event
        // sent by a released dispatch
        virtual void
        on_event(const EvPtr& event);

        private:
        Dispatch m_dispatcher;
    };

    // Base emitter
    // Derive to be able to emit
    // specific events, to be captured by distinct dispatchers
    // and listeners.
    // =======================================================
    class BaseEmitter
    {
        private:
        // Handy typedef
        using EvPtr   = std::shared_ptr<BaseEvent>;
        using DispPtr = std::unique_ptr<BaseDispatcher>;

        public:
        // Accessor methods
        // ================
        virtual void
        emit();

        virtual DispPtr
        get_dispatcher()
        {
            return std::move(this->m_dispatcher);
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
