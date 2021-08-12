#pragma once

#include "event.hpp"

namespace EventSystem
{
    /* ------------------------------------------ **
    ** Necessary forward declaration to prevent   **
    ** Incomplete types due to smart pointers     **
    /* ------------------------------------------ */
    class BaseDispatcher;

    class BaseListener
    {
        // Utility typedefs           //
        // -------------------------- //
        using EventPtr   = std::shared_ptr<Event>;
        using Dispatcher = std::shared_ptr<BaseDispatcher>;
        using Callback   = std::function<void()>;

        // Constructors           //
        // ---------------------- //
        public:
        BaseListener();
        BaseListener(Dispatcher& dispatcher);
        BaseListener(const std::map<EventPtr, Callback>& actions);

        virtual ~BaseListener() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Callback
        get_callback(const EventPtr& event);

        virtual Callback
        get_callback(const std::string& name) const;

        virtual void
        set_callback(const EventPtr& event, const Callback& cb);

        virtual void
        insert_event(const EventPtr& event, const Callback& cb);

        virtual void
        bind(const Dispatcher& dispatcher);

        // Listener functions           //
        // ---------------------------- //
        virtual void
        on_event(const EventPtr& event) = 0;

        virtual void
        on_event(const EventPtr& event, const Dispatcher& dispatcher) = 0;

        // Debugging methods           //
        // --------------------------- //
        std::string
        to_string() const;

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseListener& ls)
        {
            return os << ls.to_string();
        }

        // Bound variables           //
        // ------------------------- //
        private:
        Dispatcher m_dispatcher;

        std::map<EventPtr, Callback> m_actions;
    };
} // namespace EventSystem
