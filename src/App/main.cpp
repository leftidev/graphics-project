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

   (void)vertices;

   // You want to go from NDC (nx, ny, nz) to view space (vx, vy, vz)
   // Fortunately this is pretty simple...
   //vz = -tz / (nz - sz)  <-- Evaluate this first!
   //vx = (-vz * nx) / sx
   //vy = (-vz * ny) / sy
   
   //Shader shader;
   //shader.init(vertices);

   Vertex vertex1;
   vertex1.z = 0.0f;
   vertex1.x = -0.5f;
   vertex1.y = -0.5f;

   Vertex vertex2;
   vertex2.z = 0.0f;
   vertex2.x = 0.5f;
   vertex2.y = -0.5f;

   Vertex vertex3;
   vertex3.z = 0.0f;
   vertex3.x = 0.0f;
   vertex3.y = 0.5f;

   Triangle triangle;
   triangle.vertices[0] = vertex1;
   triangle.vertices[1] = vertex2;
   triangle.vertices[2] = vertex3;

   Vertex vertexData[3];
   vertexData[0] = {-0.5f, -0.5f, 0.0f};
   vertexData[1] = {0.5f, -0.5f, 0.0f};
   vertexData[2] = {0.0f, 0.5f, 0.0f};

   Shader shader2;
   shader2.init2(vertexData);

   // TODO: Do we need to specify glViewPort?

   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      glUseProgram(shader2.shaderProgram);
      glBindVertexArray(shader2.VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}