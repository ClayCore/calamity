#pragma once

#include "event.hpp"
#include "listener.hpp"

namespace EventSystem
{
    class BaseDispatcher
    {
        // ==== Utility typedefs ==== //
        // ========================== //
        using EventPtr = std::shared_ptr<Event>;
        using Listener = std::shared_ptr<BaseListener>;

        // ==== Constructors ==== //
        // ====================== //
        public:
        BaseDispatcher();
        BaseDispatcher(Listener& listener);
        BaseDispatcher(const std::vector<EventPtr>& events);

        virtual ~BaseDispatcher() {}

        // ==== Accessors and mutators ==== //
        // ================================ //
        virtual EventPtr
        get_event(usize index) const;

        virtual Listener
        get_listener() const;

        virtual void
        set_event(const EventPtr& event, usize index);

        virtual void
        add_event(const EventPtr& event);

        virtual void
        bind(const Listener& listener);

        // ==== Dispatcher functions ==== //
        // ============================== //
        virtual void
        dispatch(const EventPtr& event);

        virtual void
        dispatch(const EventPtr& event, const Listener& listener);

        // ==== Debugging methods ==== //
        // =========================== //
        std::string
        to_string() const;

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseDispatcher& ds)
        {
            return os << ds.to_string();
        }

        // ==== Bound variables ==== //
        // ========================= //
        private:
        Listener m_listener;

        // TODO: make this a queue or a map
        // since we might have distinct listener for many events
        std::vector<EventPtr> m_events;
    };
} // namespace EventSystem
