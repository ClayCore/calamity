#pragma once

// Include glad first
#include "opengl/glad/glad.h"
// Then glfw
#include "GLFW/glfw3.h"

// Common library
#include "zcommon.hpp"

namespace Renderer {
    auto framebuffer_size_callback(GLFWwindow* window, int width, int height) -> void {
        glViewport(0, 0, width, height);
    }

    auto R_Init() -> void {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(800, 600, "Calamity v0.1.0", NULL, NULL);
        if (window == NULL) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        while (!glfwWindowShouldClose(window)) {
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();

        return;
    }
} // namespace Renderer
