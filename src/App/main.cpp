#include <stdio.h>
#include <iostream>

#include "window.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "cube.hpp"
#include "camera.hpp"

// Converting degrees to radians
#define DEG_TO_RAD(degrees) ((degrees) * M_PI / 180.0)


Camera cam;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

void errorCallback(int error, const char* description)
{
   std::cerr << "GLFW Error " << error << ":" << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
   if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   float cameraSpeed = static_cast<float>(12.5 * deltaTime);

   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
   {
      vec3 forward{};
      // Move the camera position forward
      vec3_scale(forward, cam.cameraFront, cameraSpeed);
      vec3_add(cam.cameraPos, cam.cameraPos, forward);
   }   
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
   {
      vec3 backward{};
      // Move the camera position forward
      vec3_scale(backward, cam.cameraFront, cameraSpeed);
      vec3_sub(cam.cameraPos, cam.cameraPos, backward);
   }
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
   {
      vec3 left{};
      vec3_mul_cross(left, cam.cameraFront, cam.cameraUp);
      vec3_norm(left, left);
      vec3 test;
      vec3_scale(test, left, cameraSpeed);
      vec3_sub(cam.cameraPos, cam.cameraPos, test);
   }
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
   {
      vec3 right{};
      vec3_mul_cross(right, cam.cameraFront, cam.cameraUp);
      vec3_norm(right, right);
      vec3 test;
      vec3_scale(test, right, cameraSpeed);
      vec3_add(cam.cameraPos, cam.cameraPos, test);
   }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

   // make sure that when pitch is out of bounds, screen doesn't get flipped
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[0] = cosf(DEG_TO_RAD(yaw)) * cosf(DEG_TO_RAD(pitch));
    direction[1] = sinf(DEG_TO_RAD(pitch));
    direction[2] = sinf(DEG_TO_RAD(yaw)) * cosf(DEG_TO_RAD(pitch));
    vec3_norm(cam.cameraFront, direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}


int main(int argc, char** argv)
{
   (void)argc;
   (void)argv;

   Window window;
   window.init(800, 600, "Hello");

   // Set callbacks
   glfwSetErrorCallback(errorCallback);  
   glfwSetKeyCallback(window.getHandle(), keyCallback);
   glfwSetMouseButtonCallback(window.getHandle(), mouseButtonCallback);
   glfwSetCursorPosCallback(window.getHandle(), mouse_callback);
   glfwSetScrollCallback(window.getHandle(), scroll_callback); 
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

   // Hide and grab cursor to window for free 3D cam
   glfwSetInputMode(window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // Configure global OpenGL state
   // -----------------------------
   glEnable(GL_DEPTH_TEST);

   Renderer renderer;
   renderer.init();

   // Renderables
   Cube cube;
   cube.init();
   
   /*
   unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
   };
   */

   // Render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;  

      // Rendering commands
      glClearColor(0.2f, 1.0f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render
      renderer.draw(cube, cam);

      // Check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}