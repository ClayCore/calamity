#include "window.hpp"

// =============================== //
// ==== Window implementation ==== //
// =============================== //
namespace GFX
{
    // ==== Constructors ==== //
    // ====================== //
    Window::Window(u32 width, u32 height)
    {
        this->m_width  = width;
        this->m_height = height;
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    // ==== Window functions ==== //
    // ========================== //

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
        auto win_ptr = glfwCreateWindow(this->m_width, this->m_height, "test", NULL, NULL);

        if (win_ptr == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }

        this->m_window = std::make_unique<GLFWwindow, Utils::DestroyWindowPtr>(win_ptr);

        glfwMakeContextCurrent(this->m_window.get());
        glfwSetFramebufferSizeCallback(this->m_window.get(), frame_buffer_callback);
    }

    bool
    Window::on_update()
    {
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
            // TODO: Emit 'WindowClose' event
            return false;
        } else {
            return true;
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

} // namespace GFX::Handler
