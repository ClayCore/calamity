#pragma once

#include "event/event_system.hpp"
#include "zcommon.hpp"

// Include glad first
#include "opengl/glad/glad.h"
// Then glfw
#include "GLFW/glfw3.h"

namespace GFX
{
    namespace Handler
    {
        using namespace EventSystem;
        // ==== Window event handler ==== //
        // ============================== //
        class WindowHandler
        {
            // ==== Utility typedefs ==== //
            // ========================== //
            using EventPtr = std::shared_ptr<Event>;
            using DispPtr  = std::shared_ptr<BaseDispatcher>;
            using Callback = std::function<void()>;

            // ==== Bound structures ==== //
            // ========================== //

            // ==== List of events to be handled ==== //
            // ====================================== //
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

            // ==== Specialized emitter ============ //
            // ==== for releasing window events ==== //
            // ===================================== //
            class Emitter : public BaseEmitter
            {
                /* ========================================================= **
                ** NOTE: all methods and variables are in effect derived     **
                ** from the base class. This is why we do not need           **
                ** any accessors, constructors, mutators etc.                **
                ** ========================================================= */
            };

            // ==== Specialized dispatcher =========== //
            // ==== for processing emitted events ==== //
            // ======================================= //
            class Dispatcher : public BaseDispatcher
            {
                /* ========================================================= **
                ** NOTE: all methods and variables are in effect derived     **
                ** from the base class. This is why we do not need           **
                ** any accessors, constructors, mutators etc.                **
                ** ========================================================= */
            };

            // ==== Specialized listener ============== //
            // ==== calls functions based on event ==== //
            // ======================================== //
            class Listener : public BaseListener
            {
                /* ========================================================= **
                ** NOTE: all methods and variables are in effect derived     **
                ** from the base class. This is why we do not need           **
                ** any accessors, constructors, mutators etc.                **
                ** ========================================================= */

                // ==== Listener functions ==== //
                // ============================ //
                public:
                void
                on_event(const WindowHandler::EventPtr& event) override;

                void
                on_event(const WindowHandler::EventPtr& event, const WindowHandler::DispPtr& dispatcher) override;

                // ==== Bound variables ==== //
                // ========================= //
                WindowHandler::DispPtr m_dispatcher;

                /* ================================================ **
                ** Actions are mapped through a key-value pair      **
                ** like such:                                       **
                ** 'event => callback functor'                      **
                ** this means for every distinct event              **
                ** there is a callback function                     **
                ** ================================================ */
                std::map<WindowHandler::EventPtr, WindowHandler::Callback> m_actions;
            };

            // ==== Constructors ==== //
            // ====================== //
            public:
            WindowHandler()
            {
                this->m_emitter    = std::make_unique<Emitter>();
                this->m_dispatcher = std::make_unique<Dispatcher>();
                this->m_listener   = std::make_unique<Listener>();
            }

            // ==== Handling functions ==== //
            // ============================ //

            // ==== Debugging methods ==== //
            // =========================== //

            // ==== Bound variables ==== //
            // ========================= //
            std::unique_ptr<Emitter>    m_emitter;
            std::unique_ptr<Dispatcher> m_dispatcher;
            std::unique_ptr<Listener>   m_listener;
        };
    } // namespace Handler

    // ==== Window utilities ==== //
    // ========================== //
    namespace Utils
    {
        /* =========================================== **
        ** Supply the smart pointer to `GLFWwindow`    **
        ** with a method to destroy itself             **
        ** =========================================== */
        struct DestroyWindowPtr {
            void
            operator()(GLFWwindow* ptr)
            {
                glfwDestroyWindow(ptr);
            }
        };
    } // namespace Utils

    // ==== Main window structure ==== //
    // =============================== //
    struct Window {
        // ==== Constructors ==== //
        // ====================== //
        Window(u32 width, u32 height);

        ~Window();

        // ==== Window functions ==== //
        // ========================== //
        void
        init_glfw();

        void
        init_glad();

        void
        create_window();

        bool
        on_update();

        void
        draw();

        bool
        process_input();

        static void
        frame_buffer_callback(GLFWwindow* window, i32 width, i32 height);

        // ==== Properties ==== //
        // ==================== //
        u32 m_width;
        u32 m_height;

        // Main handler object
        Handler::WindowHandler m_handler;

        // Main glfw window
        std::unique_ptr<GLFWwindow, Utils::DestroyWindowPtr> m_window;
    };
} // namespace GFX
