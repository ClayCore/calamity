#include "manager.hpp"

namespace GFX
{
    void
    R_Init()
    {
        Window window(800, 600);

        window.init_glfw();
        window.init_glad();
        window.create_window();

        bool running = true;
        while (running) {
            running = window.on_update();
        }
    }
} // namespace GFX
