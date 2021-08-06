#pragma once

#include "zcommon.hpp"

// Include glad first
#include "opengl/glad/glad.h"
// Then glfw
#include "GLFW/glfw3.h"

namespace GFX
{
    void
    R_FrameBufferCallback(GLFWwindow* window, i32 width, i32 height);

    void
    R_ProcessInput(GLFWwindow* window);

    void
    R_Init();
} // namespace GFX
