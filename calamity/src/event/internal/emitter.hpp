#pragma once

#include "dispatcher.hpp"
#include "event.hpp"

namespace EventSystem
{
    class BaseEmitter
    {
        // Constructors           //
        // ---------------------- //
        public:
        BaseEmitter();
        BaseEmitter(Ref<BaseDispatcher>& dispatcher);
        BaseEmitter(const std::vector<Ref<Event>>& events);

        virtual ~BaseEmitter() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Ref<Event>
        get_event(usize index) const;

        virtual Ref<BaseDispatcher>
        get_dispatcher() const;

        virtual void
        set_event(const Ref<Event>& event, usize index);

        virtual void
        add_event(const Ref<Event>& event);

        virtual void
        bind(const Ref<BaseDispatcher>& dispatcher);

        // Emitter functions           //
        // --------------------------- //
        virtual void
        emit(const Ref<Event>& event);

        virtual void
        emit(const Ref<Event>& event, const Ref<BaseDispatcher>& dispatcher);

        // Debugging methods           //
        // --------------------------- //
        std::string
        to_string() const;

        friend inline std::ostream&
        operator<<(std::ostream& os, const BaseEmitter& em)
        {
            return os << em.to_string();
        }

        // Bound variables           //
        // ------------------------- //
        private:
        Ref<BaseDispatcher>     m_dispatcher;
        std::vector<Ref<Event>> m_events;
    };
} // namespace EventSystem
