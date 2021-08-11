#pragma once

#include "dispatcher.hpp"
#include "event.hpp"

namespace EventSystem
{
    class BaseEmitter
    {
        // Utility typedefs           //
        // -------------------------- //
        using EventPtr   = std::shared_ptr<Event>;
        using Dispatcher = std::shared_ptr<BaseDispatcher>;

        // Constructors           //
        // ---------------------- //
        public:
        BaseEmitter();
        BaseEmitter(Dispatcher& dispatcher);
        BaseEmitter(const std::vector<EventPtr>& events);

        virtual ~BaseEmitter() {}

        // Accessors and mutators           //
        // -------------------------------- //
        virtual EventPtr
        get_event(usize index) const;

        virtual Dispatcher
        get_dispatcher() const;

        virtual void
        set_event(const EventPtr& event, usize index);

        virtual void
        add_event(const EventPtr& event);

        virtual void
        bind(const Dispatcher& dispatcher);

        // Emitter functions           //
        // --------------------------- //
        virtual void
        emit(const EventPtr& event);

        virtual void
        emit(const EventPtr& event, const Dispatcher& dispatcher);

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
        Dispatcher            m_dispatcher;
        std::vector<EventPtr> m_events;
    };
} // namespace EventSystem
