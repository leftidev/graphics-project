#include "Window.h"

#include <stdio.h>

// Initialize GLFW, OpenGL context and glad. Create GLFW Window.
void Window::init(uint16_t width, uint16_t height, const char* title) {
    m_windowWidth = width;
    m_windowHeight = height;
    m_windowTitle = title;

    if(!glfwInit()) {
        fprintf(stderr, "Unable to initialize GLFW\n");
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle, nullptr, nullptr);
    if(!m_window) {
        fprintf(stderr, "Unable to create GLFW window\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if(!gladLoadGL()) {
        fprintf(stderr, "Unable to initialize glad\n");
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}