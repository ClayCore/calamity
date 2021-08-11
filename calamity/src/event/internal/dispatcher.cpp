#include "emitter.hpp"

namespace EventSystem
{
    // Constructors           //
    // ---------------------- //
    BaseDispatcher::BaseDispatcher() {}

    BaseDispatcher::BaseDispatcher(Listener& listener)
    {
        this->m_listener = listener;
    }

    BaseDispatcher::BaseDispatcher(const std::vector<EventPtr>& events)
    {
        this->m_events = events;
    }

    // Accessors and mutators           //
    // -------------------------------- //
    auto
    BaseDispatcher::get_event(usize index) const -> EventPtr
    {
        if (index < this->m_events.size()) {
            return this->m_events[index];
        }
    }

    auto
    BaseDispatcher::get_listener() const -> Listener
    {
        return this->m_listener;
    }

    void
    BaseDispatcher::set_event(const EventPtr& event, usize index)
    {
        if (index < this->m_events.size()) {
            auto offset = (this->m_events.begin() + index);

            this->m_events.insert(offset, event);
        }
    }

    void
    BaseDispatcher::add_event(const EventPtr& event)
    {
        this->m_events.push_back(event);
    }

    void
    BaseDispatcher::bind(const Listener& listener)
    {
        this->m_listener = listener;
    }

    // Dispatcher functions           //
    // ------------------------------ //
    void
    BaseDispatcher::dispatch(const EventPtr& event)
    {
        this->m_listener->on_event(event);
    }

    void
    BaseDispatcher::dispatch(const EventPtr& event, const Listener& listener)
    {
        listener->on_event(event);
    }

    // Debugging methods           //
    // --------------------------- //
    std::string
    BaseDispatcher::to_string() const
    {
        std::vector<std::string> buffer;
        buffer.push_back("Dispatcher: \n");

        for (auto it = this->m_events.begin(); it < this->m_events.end(); ++it) {
            // Extract the event
            EventPtr event = *it;

            // Fetch the name
            std::string event_name = event->to_string();

            // Get the index of the current iteration
            usize index = std::distance(this->m_events.begin(), it);

            // Format into a string
            auto format = "\tEventID: %u -- [%s]\n";
            auto size   = std::snprintf(nullptr, 0, format);

            std::string output(size + 1, '\0');
            std::sprintf(&output[0], format, index, event_name.c_str());

            buffer.push_back(output);
        }

        // Implode the buffer into a single string
        std::ostringstream implode;
        std::copy(buffer.begin(), buffer.end(),
                  std::ostream_iterator<std::string>(implode, "\n"));

        return implode.str();
    }
} // namespace EventSystem
