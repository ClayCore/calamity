#include "manager.hpp"

namespace GFX
{
    void
    R_FrameBufferCallback(GLFWwindow* window, i32 width, i32 height)
    {
        glViewport(0, 0, width, height);
    }

    void
    R_ProcessInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void
    R_Init()
    {
        std::cout << "Initializing graphics manager" << std::endl;

        // Initialize and configure glfw
        // =============================
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Window creation
        // TODO: move to a separate function, maybe class
        // and isolate the arguments (constants)
        // ==============================================
        GLFWwindow* window = glfwCreateWindow(800, 600, "Calamity v0.1.0", NULL, NULL);
        if (window == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, R_FrameBufferCallback);

        // Loads all OpenGL function pointers
        // ==================================
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        // Render loop
        // TODO: create a better draw function
        // and add event polling
        // ===================================
        while (!glfwWindowShouldClose(window)) {
            // Input processing
            // ================
            R_ProcessInput(window);

            // Do rendering
            // ============
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap buffers and poll I/O events
            // ================================
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

        return;
    }
} // namespace GFX
