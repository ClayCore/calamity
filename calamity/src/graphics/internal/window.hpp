#pragma once

#include "event/event.hpp"
#include "zcommon.hpp"

namespace GFX
{
    // Window structure.
    // defines the main window,
    // used for rendering
    // ========================
    struct Window {
        u32           m_width;
        u32           m_height;
        WindowHandler m_handler;

        Window(u32 width, u32 height) : m_width(width), m_height(height)
        {
            this->m_handler = WindowHandler();
        }

        void
        on_update()
        {
            // Create an event emitter
            auto base_emitter = std::unique_ptr<EventSystem::BaseEmitter>();

            // cast it to a window emitter
            auto emitter = dynamic_cast<WindowHandler::Emitter*>(base_emitter.get());

            // emit the event
        }

        void
        draw()
        {
            std::cout << "drawing to screen!" << std::endl;
        }
    };

    // Window event handler
    // ====================
    class WindowHandler
    {
        private:
        // Handy typedefs
        using BEmitter    = EventSystem::BaseEmitter;
        using BDispatcher = EventSystem::BaseDispatcher;
        using BListener   = EventSystem::BaseListener;
        using BEvent      = EventSystem::BaseEvent;

        public:
        // Main emitter for the window handler
        // used for sending events to the dispatcher
        // =========================================
        class Emitter : BEmitter
        {
            public:
            // Emits an event to a distinct dispatcher
            // =======================================
            void
            emit(const EvPtr& event, DispPtr& dispatcher);
        };

        // Main dispatch construct
        // used for capturing and releasing
        // window events
        // ================================
        class Dispatcher : BDispatcher
        {
            public:
            // Sends an event to a listener
            // ============================
            void
            dispatch(const Listener& listener);

            void
            add_event(const EvPtr& event);

            // Accessors
            // =========
            const char*
            get_event_name(usize index) const;

            const EventSystem::EventType
            get_type(usize index) const;
        };

        // Main listener construct
        // used for acting upon a signal
        // and handling events
        // =============================
        class Listener : BListener
        {
            // Fetches a callback from the main map
            // based on the type and calls it
            // ====================================
            void
            on_event(const EvPtr& event, const Callback& cb);
        };
    };
} // namespace GFX
