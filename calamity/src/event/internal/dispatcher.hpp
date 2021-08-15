#pragma once

#include "event.hpp"
#include "listener.hpp"

namespace EventSystem
{
    class BaseDispatcher
    {
        // Constructors           //
        // ---------------------- //
        public:
        BaseDispatcher();
        BaseDispatcher(Ref<BaseListener>& listener);
        BaseDispatcher(const std::vector<Ref<Event>>& events);

        virtual ~BaseDispatcher() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Ref<Event>
        get_event(usize index) const;

        virtual Ref<BaseListener>
        get_listener() const;

        virtual void
        set_event(const Ref<Event>& event, usize index);

        virtual void
        add_event(const Ref<Event>& event);

        virtual void
        bind(const Ref<BaseListener>& listener);

        // Dispatcher functions           //
        // ------------------------------ //
        virtual void
        dispatch(const Ref<Event>& event);

        virtual void
        dispatch(const Ref<Event>& event, const Ref<BaseListener>& listener);

        // Debugging methods           //
        // --------------------------- //
        std::string
        to_string() const;

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseDispatcher& ds)
        {
            return os << ds.to_string();
        }

        // Bound variables           //
        // ------------------------- //
        private:
        Ref<BaseListener> m_listener;

        // TODO: make this a queue or a map
        // since we might have distinct listener for many events
        std::vector<Ref<Event>> m_events;
    };
} // namespace EventSystem
