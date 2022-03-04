#include <stdio.h>

#include "Window.h"
#include "Shader.h"
#include "Cube.h"


const unsigned int WINDOWWIDTH = 800;
const unsigned int WINDOWHEIGHT = 600;


void errorCallback(int error, const char* description)
{
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        printf("Key E PRESSED!\n");
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
   if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
   (void)window;
   glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void translate(unsigned int ShaderID, mat4x4 MVP, float x)
{
   mat4x4_identity(MVP);

   mat4x4_translate(MVP, x, 0.0f, -0.9f);

/*
   int i,j;
   for(i=0; i<4; ++i) {
      for(j=0; j<4; ++j)
         printf("%f, ", MVP[i][j]);
      printf("\n");
   }
*/

   GLuint MatrixID = glGetUniformLocation(ShaderID, "MVP");

   // Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

int main(int argc, char** argv)
{
   (void)argc;
   (void)argv;
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(WINDOWWIDTH, WINDOWHEIGHT, "Hello");

   // Set callbacks
   glfwSetKeyCallback(window.getHandle(), keyCallback);
   glfwSetMouseButtonCallback(window.getHandle(), mouseButtonCallback);
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

   Shader shader;
   shader.init();

   // Cube vertex data
   Vertex vertices[] = {
      {-0.5f, -0.5f, 0.0f},
      { 0.5f, -0.5f, 0.0f}, 
      { 0.0f,  0.5f, 0.0f}
   };

   Cube cube;
   cube.init(*vertices);

   // Model View Projection matrix
   mat4x4 MVP;

   float x = 0.0f;

   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      // TODO: Stopped here while testing linmath and mat4x4
      shader.use();

      translate(shader.shaderProgram, MVP, x);

      cube.draw();

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}

