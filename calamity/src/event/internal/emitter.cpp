#include "emitter.hpp"

namespace Calamity::EventSystem
{
    // Constructors           //
    // ---------------------- //
    BaseEmitter::BaseEmitter() {}

    BaseEmitter::BaseEmitter(Ref<BaseDispatcher> dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    // Accessors and mutators           //
    // -------------------------------- //
    auto
    BaseEmitter::get_event(usize index) const -> Ref<Event>
    {
        if (index < this->m_events.size()) {
            return this->m_events[index];
        } else {
            return nullptr;
        }
    }

    auto
    BaseEmitter::get_dispatcher() const -> Ref<BaseDispatcher>
    {
        return this->m_dispatcher;
    }

    void
    BaseEmitter::set_event(Scope<Event> event, usize index)
    {
        if (index < this->m_events.size()) {
            auto offset = (this->m_events.begin() + static_cast<isize>(index));

            this->m_events.insert(offset, std::move(event));
        }
    }

    void
    BaseEmitter::add_event(Scope<Event> event)
    {
        this->m_events.push_back(std::move(event));
    }

    void
    BaseEmitter::bind(Ref<BaseDispatcher> dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    // Emitter functions           //
    // --------------------------- //
    void
    BaseEmitter::emit(Scope<Event> event)
    {
        this->m_dispatcher->dispatch(std::move(event));
    }

    void
    BaseEmitter::emit(Scope<Event> event, Ref<BaseDispatcher> dispatcher)
    {
        dispatcher->dispatch(std::move(event));
    }

    // Debugging methods           //
    // --------------------------- //
    std::string
    BaseEmitter::to_string() const
    {
        std::vector<std::string> buffer;
        buffer.push_back("Emitter: \n");

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
