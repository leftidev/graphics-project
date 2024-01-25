#include "window.hpp"

#include <stdio.h>

// Initialize GLFW, OpenGL context and glad. Create GLFW Window.
void Window::init(uint16_t width, uint16_t height, const std::string& title) {
    if(!glfwInit()) {
        std::cerr << "Unable to initialize GLFW" << std::endl;
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!m_window) {
        std::cerr << "Unable to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);

    if(!gladLoadGL()) {
        std::cerr << "Unable to initialize glad" << std::endl;
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}