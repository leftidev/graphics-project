#pragma once

#include <stdint.h>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Window {
public:
    Window(): m_window(nullptr) {};
    ~Window() {};

    void init(uint16_t width, uint16_t, const char* title);
    inline GLFWwindow* getHandle() { return m_window; };

private:
    GLFWwindow* m_window;
    const char* m_windowTitle;
    uint16_t m_windowWidth;
    uint16_t m_windowHeight;
};