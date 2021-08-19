#include "emitter.hpp"

namespace Calamity::EventSystem
{
    // Constructors           //
    // ---------------------- //
    BaseDispatcher::BaseDispatcher() {}

    BaseDispatcher::BaseDispatcher(Ref<BaseListener>& listener)
    {
        this->m_listener = listener;
    }

    // Accessors and mutators           //
    // -------------------------------- //
    auto
    BaseDispatcher::get_event(usize index) const -> Ref<Event>
    {
        if (index < this->m_events.size()) {
            return this->m_events[index];
        } else {
            return nullptr;
        }
    }

    auto
    BaseDispatcher::get_listener() const -> Ref<BaseListener>
    {
        return this->m_listener;
    }

    void
    BaseDispatcher::set_event(Scope<Event> event, usize index)
    {
        if (index < this->m_events.size()) {
            auto offset = (this->m_events.begin() + static_cast<isize>(index));

            this->m_events.insert(offset, std::move(event));
        }
    }

    void
    BaseDispatcher::add_event(Scope<Event> event)
    {
        this->m_events.push_back(std::move(event));
    }

    void
    BaseDispatcher::bind(Ref<BaseListener> listener)
    {
        this->m_listener = listener;
    }

    // Dispatcher functions           //
    // ------------------------------ //
    void
    BaseDispatcher::dispatch(Scope<Event> event)
    {
        this->m_listener->on_event(std::move(event));
    }

    void
    BaseDispatcher::dispatch(Scope<Event> event, Ref<BaseListener> listener)
    {
        listener->on_event(std::move(event));
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
            Ref<Event> event = *it;

            // Fetch the name
            std::string event_name = event->to_string();

            // Get the index of the current iteration
            isize index = std::distance(this->m_events.begin(), it);

            // Format into a string
            auto format   = "\tEventID: %u -- [%s]\n";
            auto size_raw = std::snprintf(nullptr, 0, format, index, event_name.c_str());

            usize size = static_cast<usize>(std::abs(size_raw));

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
} // namespace Calamity::EventSystem
