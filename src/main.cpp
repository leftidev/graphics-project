#include <stdio.h>

#include "Window.h"

void errorCallback(int error, const char* description) {
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int argc, char** argv) {
   (void)argc;
   (void)argv;
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(800, 600, "Hello");

   glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

   while (!glfwWindowShouldClose(window.getHandle())) {
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}