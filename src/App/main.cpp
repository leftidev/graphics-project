#include <stdio.h>
#include <iostream>

#include "window.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "cube.hpp"
#include "camera.hpp"


Camera cam;

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
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
   {
      vec3 forward{};
      // Move the camera position forward
      vec3_scale(forward, cam.cameraFront, cam.cameraSpeed);
      vec3_add(cam.cameraPos, cam.cameraPos, forward);
   }   
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
   {
      vec3 backward{};
      // Move the camera position forward
      vec3_scale(backward, cam.cameraFront, cam.cameraSpeed);
      vec3_sub(cam.cameraPos, cam.cameraPos, backward);
   }
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
   {
      vec3 left{};
      vec3_mul_cross(left, cam.cameraFront, cam.cameraUp);
      vec3_norm(left, left);
      vec3 test;
      vec3_scale(test, left, cam.cameraSpeed);
      vec3_sub(cam.cameraPos, cam.cameraPos, test);
   }
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
   {
      vec3 right{};
      vec3_mul_cross(right, cam.cameraFront, cam.cameraUp);
      vec3_norm(right, right);
      vec3_add(cam.cameraPos, cam.cameraPos, right);
   }
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
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

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