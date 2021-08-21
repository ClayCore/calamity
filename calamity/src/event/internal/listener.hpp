#pragma once

#include "event.hpp"

namespace Calamity::EventSystem
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

        virtual ~BaseListener() = default;

        // Accessors and mutators           //
        // -------------------------------- //
        virtual Callback get_callback(Scope<Event> event);

        virtual Callback get_callback(const std::string& name) const;

        virtual void set_callback(Scope<Event> event, const Callback& cb);

        virtual void insert_event(Scope<Event> event, const Callback& cb);

        virtual void bind(Ref<BaseDispatcher> dispatcher);

        // Listener functions           //
        // ---------------------------- //
        virtual void on_event(Scope<Event> event) = 0;

        virtual void on_event(Scope<Event> event, Ref<BaseDispatcher> dispatcher) = 0;

        // Debugging methods           //
        // --------------------------- //
        std::string to_string() const;

        friend inline std::ostream& operator<<(std::ostream& os, const BaseListener& ls)
        {
            return os << ls.to_string();
        }

        // Bound variables           //
        // ------------------------- //
      private:
        Ref<BaseDispatcher> m_dispatcher;

        std::map<Event, Callback> m_actions;
    };
}  // namespace Calamity::EventSystem
