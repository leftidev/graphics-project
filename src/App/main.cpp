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

int main(int argc, char** argv)
{
   (void)argc;
   (void)argv;
   
   glfwSetErrorCallback(errorCallback);

   Window window;
   window.init(WINDOWWIDTH, WINDOWHEIGHT, "Hello");

   // Set callbacks
   glfwSetMouseButtonCallback(window.getHandle(), mouseButtonCallback);
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

   Shader shader;
   shader.init();

   Vertex vertexData[3];
   vertexData[0] = {-0.5f, -0.5f, 0.0f};
   vertexData[1] = {0.5f, -0.5f, 0.0f};
   vertexData[2] = {0.0f, 0.5f, 0.0f};

   Vertex vertexData2[] = {{-1.5f, -0.2f, 0.0f}, {0.5f, -0.15f, 0.0f}, {0.0f, 0.35f, 0.0f}};
   Vertex vertexData3[] = {{1.0f, -1.0f, 0.0f}, {0.8f, -0.8f, 0.0f}, {1.0f, 1.0f, 0.0f}};

   Cube cube;
   cube.init(vertexData);

   Cube cube2;
   cube2.init2(vertexData2);

   Cube cube3;
   cube3.init3(*vertexData3);

   mat4x4 MVP;

   float x = -0.7f;

   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      // TODO: Stopped here while testing linmath and mat4x4
      shader.use(MVP, x);

      cube.draw();
      cube2.draw();
      cube3.draw();

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}

