#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>


class Window {
public:
    Window() = default;
    ~Window() = default;

    void init(uint16_t width, uint16_t height, const std::string& title);
    GLFWwindow* getHandle() { return m_window; };

private:
    GLFWwindow* m_window = nullptr;
};