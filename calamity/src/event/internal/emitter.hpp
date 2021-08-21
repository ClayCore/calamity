#pragma once

#include "dispatcher.hpp"
#include "event.hpp"

namespace Calamity::EventSystem
{
    class BaseEmitter
    {
        // Constructors           //
        // ---------------------- //
      public:
        BaseEmitter();
        BaseEmitter(Ref<BaseDispatcher> dispatcher);

        virtual ~BaseEmitter() = default;

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Ref<Event> get_event(usize index) const;

        virtual Ref<BaseDispatcher> get_dispatcher() const;

        virtual void set_event(Scope<Event> event, usize index);

        virtual void add_event(Scope<Event> event);

        virtual void bind(Ref<BaseDispatcher> dispatcher);

        // Emitter functions           //
        // --------------------------- //
        virtual void emit(Scope<Event> event);

        virtual void emit(Scope<Event> event, Ref<BaseDispatcher> dispatcher);

        // Debugging methods           //
        // --------------------------- //
        std::string to_string() const;

        friend inline std::ostream& operator<<(std::ostream& os, const BaseEmitter& em)
        {
            return os << em.to_string();
        }

        // Bound variables           //
        // ------------------------- //
      private:
        Ref<BaseDispatcher> m_dispatcher;
        std::vector<Ref<Event>> m_events;
    };
}  // namespace Calamity::EventSystem
