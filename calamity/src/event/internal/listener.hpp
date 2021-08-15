#pragma once

#include "event.hpp"

namespace EventSystem
{
    /* ------------------------------------------ **
    ** Necessary forward declaration to prevent   **
    ** Incomplete types due to smart pointers     **
    ** ------------------------------------------ */
    class BaseDispatcher;

    class BaseListener
    {
        // Utility typedefs           //
        // -------------------------- //
        using Callback = std::function<void()>;

        // Constructors           //
        // ---------------------- //
        public:
        BaseListener();
        BaseListener(Ref<BaseDispatcher>& dispatcher);
        BaseListener(const std::map<Event, Callback>& actions);

        virtual ~BaseListener() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Callback
        get_callback(const Ref<Event>& event);

        virtual Callback
        get_callback(const std::string& name) const;

        virtual void
        set_callback(const Ref<Event>& event, const Callback& cb);

        virtual void
        insert_event(const Ref<Event>& event, const Callback& cb);

        virtual void
        bind(const Ref<BaseDispatcher>& dispatcher);

        // Listener functions           //
        // ---------------------------- //
        virtual void
        on_event(const Ref<Event>& event) = 0;

        virtual void
        on_event(const Ref<Event>& event, const Ref<BaseDispatcher>& dispatcher) = 0;

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
        Ref<BaseDispatcher> m_dispatcher;

        std::map<Event, Callback> m_actions;
    };
} // namespace EventSystem
