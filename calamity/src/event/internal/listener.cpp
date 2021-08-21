#include "listener.hpp"

namespace Calamity::EventSystem
{
    // Constructors           //
    // ---------------------- //
    BaseListener::BaseListener()
    {
    }

    BaseListener::BaseListener(Ref<BaseDispatcher>& dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    // Accessors and mutators           //
    // -------------------------------- //
    auto BaseListener::get_callback(Scope<Event> event) -> Callback
    {
        auto ev = *event;
        return this->m_actions[ev];
    }

    auto BaseListener::get_callback(const std::string& name) const -> Callback
    {
        for (auto&& [event, callback] : this->m_actions) {
            if (std::strcmp(event.get_name(), name.data()) == 0) { return callback; }
        }
    }

    void BaseListener::set_callback(Scope<Event> event, const Callback& cb)
    {
        this->m_actions[*event] = cb;
    }

    void BaseListener::insert_event(Scope<Event> event, const Callback& cb)
    {
        this->m_actions.emplace(*event, cb);
    }

    void BaseListener::bind(Ref<BaseDispatcher> dispatcher)
    {
        this->m_dispatcher = dispatcher;
    }

    // Debugging methods           //
    // --------------------------- //
    std::string BaseListener::to_string() const
    {
        std::vector<std::string> buffer;
        buffer.push_back("Listener: \n");

        for (auto it = this->m_actions.begin(); it != this->m_actions.end(); ++it) {
            // Extract the event
            Event event = it->first;

            // Fetch the name
            std::string event_name = event.to_string();

            // Get the index of the current iteration
            isize index = std::distance(this->m_actions.begin(), it);

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
        std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(implode, "\n"));

        return implode.str();
    }
}  // namespace Calamity::EventSystem
