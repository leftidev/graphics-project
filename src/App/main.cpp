#include <stdio.h>

#include "Window.h"
#include "Shader.h"
#include "Sprite.h"

const unsigned int WINDOWWIDTH = 800;
const unsigned int WINDOWHEIGHT = 600;

void errorCallback(int error, const char* description) {
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   (void)window;
   glViewport(0, 0, width, height);
}

int main(int argc, char** argv) {
   (void)argc;
   (void)argv;
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(WINDOWWIDTH, WINDOWHEIGHT, "Hello");

   glfwSetFramebufferSizeCallback(window.getHandle(), framebuffer_size_callback);

   Shader shader;
   shader.init();

   Sprite sprite;
   sprite.init();

   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      shader.use();

      sprite.draw();

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}

