#pragma once

#include "zcommon.hpp"

// Include glad first
#include "opengl/glad/glad.h"
// Then glfw
#include "GLFW/glfw3.h"

namespace GFX {
    auto R_FrameBufferCallback(GLFWwindow* window, i32 width, i32 height) -> void;

    auto R_ProcessInput(GLFWwindow* window) -> void;

    auto R_Init() -> void;
} // namespace GFX
