#include <stdio.h>

#include "Window.h"
#include "Shader.h"



void errorCallback(int error, const char* description) {
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv) {
   (void)argc;
   (void)argv;
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(800, 600, "Hello");

   // Specify 3 vertices with each vertex having a 3D position (x, y, z)
   // To render a 2D triangle, each vertex has z coord of 0.0
   float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
   };  
   
   Shader shader;
   shader.init(vertices);
   // TODO: Do we need to specify glViewPort?

   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      glUseProgram(shader.shaderProgram);
      glBindVertexArray(shader.VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}