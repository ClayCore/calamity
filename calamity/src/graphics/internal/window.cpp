#include "window.hpp"

// =============================== //
// ==== Window implementation ==== //
// =============================== //
namespace GFX
{
    using namespace EventSystem;

    // Constructors           //
    // ---------------------- //
    Window::Window(u32 width, u32 height)
    {
        this->m_width  = width;
        this->m_height = height;

        auto event      = std::make_unique<Event>(EventType::WindowClose);
        auto close_func = [&]() { this->close_window(); };

        this->m_handler.m_listener->set_callback(std::move(event), close_func);
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    // Utility functions           //
    // --------------------------- //
    void
    Window::send_update()
    {
        auto event = std::make_unique<Event>(EventType::EngineUpdate);

        this->m_handler.emit_event(std::move(event));
    }

    // Window functions           //
    // -------------------------- //

    // Initializes and configures glfw
    void
    Window::init_glfw()
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    // Initializes glad
    void
    Window::init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize glad" << std::endl;
            return;
        }
    }

    // Creates the main window
    void
    Window::create_window()
    {
        auto win_ptr =
            glfwCreateWindow(this->m_width, this->m_height, "test", NULL, NULL);

        if (win_ptr == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        this->m_window = std::unique_ptr<GLFWwindow, Utils::DestroyWindowPtr>(win_ptr);

        glfwMakeContextCurrent(this->m_window.get());
        glfwSetFramebufferSizeCallback(this->m_window.get(), frame_buffer_callback);

        this->send_update();
    }

    void
    Window::close_window()
    {
        glfwSetWindowShouldClose(this->m_window.get(), true);
    }

    bool
    Window::on_update()
    {
        this->send_update();

        bool result = this->process_input();

        this->draw();

        glfwSwapBuffers(this->m_window.get());
        glfwPollEvents();

        return result;
    }

    void
    Window::draw()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Handles input
    bool
    Window::process_input()
    {
        if (glfwGetKey(this->m_window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            auto event = std::make_unique<Event>(EventType::WindowClose);
            this->m_handler.m_emitter->emit(std::move(event));

            glfwSetWindowShouldClose(this->m_window.get(), true);
        }
    }

    // Redraw viewport each time the window is resized
    void
    Window::frame_buffer_callback(GLFWwindow* window, i32 width, i32 height)
    {
        glViewport(0, 0, width, height);
    }
} // namespace GFX

// ====================================== //
// ==== Event handler implementation ==== //
// ====================================== //
namespace GFX::Handler
{
    using namespace EventSystem;

    void
    WindowHandler::emit_event(const WindowHandler::EventPtr& event)
    {
        this->m_emitter->emit(event);
    }

    void
    WindowHandler::Listener::on_event(const WindowHandler::EventPtr& event)
    {
        switch (H_GetHash(event->get_name())) {
            case "EngineUpdate"_hash: {
                // Call functor and dispatch next update event
                this->m_actions[event]();

                this->m_dispatcher->dispatch(event);
            } break;
            case "WindowClose"_hash: {
                this->m_actions[event]();
            } break;
            default: {
                // Unimplemented.
            }
        }
    }

    void
    WindowHandler::Listener::on_event(const WindowHandler::EventPtr& event,
                                      const WindowHandler::DispPtr&  dispatcher)
    {
    }

} // namespace GFX::Handler
