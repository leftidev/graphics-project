#include <stdio.h>

#include "Window.h"

void errorCallback(int error, const char* description) {
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void colorFlicker(float time) {
   glClearColor(time, time / 10.0f, time / 50.0f, 1.0f);
}

int main(int argc, char** argv) {
   (void)argc;
   (void)argv;

   
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(800, 600, "Hello");

   while (!glfwWindowShouldClose(window.getHandle())) {
      float time = (float)glfwGetTime() * 0.1f;
      colorFlicker(time);

      glClear(GL_COLOR_BUFFER_BIT);
   
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}