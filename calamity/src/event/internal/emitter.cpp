#include "emitter.hpp"

namespace EventSystem
{
    // ==== Constructors ==== //
    // ====================== //
    BaseEmitter::BaseEmitter() {}

    BaseEmitter::BaseEmitter(Dispatcher& dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    BaseEmitter::BaseEmitter(const std::vector<EventPtr>& events)
    {
        this->m_events = events;
    }

    // ==== Accessors and mutators ==== //
    // ================================ //
    auto
    BaseEmitter::get_event(usize index) const -> EventPtr
    {
        if (index < this->m_events.size()) {
            return this->m_events[index];
        }
    }

    auto
    BaseEmitter::get_dispatcher() const -> Dispatcher
    {
        return this->m_dispatcher;
    }

    void
    BaseEmitter::set_event(const EventPtr& event, usize index)
    {
        if (index < this->m_events.size()) {
            auto offset = (this->m_events.begin() + index);

            this->m_events.insert(offset, event);
        }
    }

    void
    BaseEmitter::add_event(const EventPtr& event)
    {
        this->m_events.push_back(event);
    }

    void
    BaseEmitter::bind(const Dispatcher& dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    // ==== Emitter functions ==== //
    // =========================== //
    void
    BaseEmitter::emit(const EventPtr& event)
    {
        this->m_dispatcher->dispatch(event);
    }

    void
    BaseEmitter::emit(const EventPtr& event, const Dispatcher& dispatcher)
    {
        dispatcher->dispatch(event);
    }

    // ==== Debugging methods ==== //
    // =========================== //
    std::string
    BaseEmitter::to_string() const
    {
        std::vector<std::string> buffer;
        buffer.push_back("Emitter: \n");

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
        std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

        return implode.str();
    }
} // namespace EventSystem
