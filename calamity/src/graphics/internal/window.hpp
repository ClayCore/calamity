#pragma once

#include "event/event.hpp"
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

        Window(u32 width, u32 height) : m_width(width), m_height(height)
        {
            this->m_handler = WindowHandler();
        }

        void
        on_update()
        {
            auto event = std::make_unique<BaseEvent>(EventType::EngineUpdate);
        }

        void
        draw();
    };

    // Window event handler
    // ====================
    class WindowHandler
    {
    };
} // namespace GFX
