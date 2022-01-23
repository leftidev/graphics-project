#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>


void errorCallback(int error, const char* description) {
   fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

GLFWwindow* initialize() {
   glfwTerminate();
   fprintf(stderr, "1Unable to initialize GLFW\n");
   int glfwInitRes = glfwInit();
   fprintf(stderr, "2Unable to initialize GLFW\n");
   if (!glfwInitRes) {
      fprintf(stderr, "Unable to initialize GLFW\n");
      return nullptr;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
   if (!window) {
      fprintf(stderr, "Unable to create GLFW window\n");
      glfwTerminate();
      return nullptr;
   }

   glfwMakeContextCurrent(window);

   int gladInitRes = gladLoadGL();
   if (!gladInitRes) {
      fprintf(stderr, "Unable to initialize glad\n");
      glfwDestroyWindow(window);
      glfwTerminate();
      return nullptr;
   }

   return window;
}


int main(void) {
   glfwSetErrorCallback(errorCallback);

   GLFWwindow* window = initialize();

   glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      //fprintf(stderr, "6Unable to initialize GLFW\n");
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}