#pragma once

#include "event/event_system.hpp"
#include "zcommon.hpp"

namespace GFX
{
    using namespace EventSystem;

    // Window structure.
    // defines the main window,
    // used for rendering
    // ========================
    struct Window {
        u32           m_width;
        u32           m_height;
        WindowHandler m_handler;

        Window(u32 width, u32 height) : m_width(width), m_height(height) {}

        void
        on_update()
        {
            auto                   event        = std::make_unique<Event>(EventType::EngineUpdate);
            std::shared_ptr<Event> shared_event = std::move(event);

            m_handler.m_emitter->emit(shared_event);
        }

        void
        draw();
    };

    // Window event handler
    // ====================
    class WindowHandler
    {
        // Utility typedefs
        // ================
        using EventPtr = std::shared_ptr<Event>;
        using DispPtr  = std::shared_ptr<BaseDispatcher>;
        using Callback = std::function<void()>;

        // Bound structures
        // ================

        // List of events to be handled

        // clang-format off
        const Event m_EventList[7] { 
            { EventType::WindowClose        },
            { EventType::WindowFocus        },
            { EventType::WindowLostFocus    },
            { EventType::WindowMoved        },
            { EventType::WindowResize       },
            { EventType::EngineUpdate       },
            { EventType::EngineRender       }
        };
        // clang-format on

        // Specialized emitter
        // for releasing window events
        // ===========================
        class Emitter : public BaseEmitter
        {
        };

        // Specialized dispatcher
        // for processing emitted events
        // =============================
        class Dispatcher : public BaseDispatcher
        {
        };

        // Specialized listener
        // calls functions based on event
        // ==============================
        class Listener : public BaseListener
        {
            public:
            void
            on_event(const WindowHandler::EventPtr& event) override
            {
                auto functor = this->m_actions[event];

                functor();
            }

            void
            on_event(const WindowHandler::EventPtr& event, const WindowHandler::DispPtr& dispatcher)
            {
                // TODO: switch-case event
                // and send event back into dispatcher.
            }

            WindowHandler::DispPtr m_dispatcher;

            std::map<WindowHandler::EventPtr, WindowHandler::Callback> m_actions;
        };

        // Constructors
        // ============
        public:
        WindowHandler()
        {
            this->m_emitter    = std::make_unique<Emitter>();
            this->m_dispatcher = std::make_unique<Dispatcher>();
            this->m_listener   = std::make_unique<Listener>();
        }

        // Handling functions
        // ==================

        // Debugging methods
        // =================

        // Bound methods and variables
        // ===========================
        std::unique_ptr<Emitter>    m_emitter;
        std::unique_ptr<Dispatcher> m_dispatcher;
        std::unique_ptr<Listener>   m_listener;
    };
} // namespace GFX
