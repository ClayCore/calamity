#include "manager.hpp"

namespace GFX
{
    void
    R_Init()
    {
        Window window(800, 600);

        window.init_glfw();
        window.create_window();
        window.init_glad();

        bool running = true;
        while (running && !glfwWindowShouldClose(window.m_window.get())) {
            running = window.on_update();
        }
    }
} // namespace GFX
