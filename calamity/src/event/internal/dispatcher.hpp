#pragma once

#include "event.hpp"
#include "listener.hpp"

namespace Calamity::EventSystem
{
    class BaseDispatcher
    {
        // Constructors           //
        // ---------------------- //
      public:
        BaseDispatcher();
        BaseDispatcher(Ref<BaseListener>& listener);

        virtual ~BaseDispatcher() = default;

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Ref<Event> get_event(usize index) const;

        virtual Ref<BaseListener> get_listener() const;

        virtual void set_event(Scope<Event> event, usize index);

        virtual void add_event(Scope<Event> event);

        virtual void bind(Ref<BaseListener> listener);

        // Dispatcher functions           //
        // ------------------------------ //
        virtual void dispatch(Scope<Event> event);

        virtual void dispatch(Scope<Event> event, Ref<BaseListener> listener);

        // Debugging methods           //
        // --------------------------- //
        std::string to_string() const;

        friend inline std::ostream& operator<<(std::ostream& os, const BaseDispatcher& ds)
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
}  // namespace Calamity::EventSystem
