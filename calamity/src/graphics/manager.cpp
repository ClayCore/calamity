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

        window.on_update();
    }
} // namespace GFX
