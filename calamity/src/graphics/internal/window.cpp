#include "window.hpp"

namespace GFX
{
    // Emitter method definitions
    // ==========================
    void
    WindowHandler::Emitter::emit(const EvPtr& event, DispPtr& dispatcher)
    {
        dispatcher->add_event(event);
    }

    // Dispatcher method definitions
    // =============================
    void
    WindowHandler::Dispatcher::dispatch(const Listener& listener)
    {
        for (auto& i : this->m_events) {
            listener->on_event(i);
        }
    }

    void
    WindowHandler::Dispatcher::add_event(const EvPtr& event)
    {
        this->m_events.push_back(event);
    }

    const char*
    WindowHandler::Dispatcher::get_event_name(usize index) const
    {
        // Check the vector bounds
        if (index >= 0 && index < this->m_events.size()) {
            return this->m_events[index]->get_name();
        }
    }

    const EventSystem::EventType
    WindowHandler::Dispatcher::get_type(usize index) const
    {
        // Check the vector bounds
        if (index >= 0 && index < this->m_events.size()) {
            return this->m_events[index]->get_type();
        }
    }

    // Listener method definitions
    // ===========================
    void
    WindowHandler::Listener::on_event(const EvPtr& event, const Callback& cb)
    {
        auto event_type = event->get_type();

        this->call_func(event_type);
    }
} // namespace GFX
