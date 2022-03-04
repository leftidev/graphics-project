#include <stdio.h>

#include "Window.h"
#include "Shader.h"
#include "Cube.h"


const unsigned int WINDOWWIDTH = 800;
const unsigned int WINDOWHEIGHT = 600;

// GLOBAL VARIABLES (Don't worry; For testing purposes)
static float x = 0.0f;
static float y = 0.0f;
static float z = 0.0f;

static float sx = 1.0f;
static float sy = 1.0f;
static float sz = 1.0f;


void errorCallback(int error, const char* description)
{
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_UP && action == GLFW_PRESS)
   {
      y += 0.1f;
      printf("Up pressed!\n");
   }
   if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
   {
      y -= 0.1f;
      printf("Down pressed!\n");
   }  
   if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
   {
      x -= 0.1f;
      printf("Left pressed!\n");
   }
   if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
   {
      x += 0.1f;
      printf("Right pressed!\n");
   }
   if (key == GLFW_KEY_Z && action == GLFW_PRESS)
   {
      sz += 0.1f;
      printf("Z pressed!\n");
   }
   if (key == GLFW_KEY_X && action == GLFW_PRESS)
   {
      sz -= 0.1f;
      printf("X pressed!\n");
   }
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

void translate(unsigned int ShaderID, mat4x4 MVP)
{
   mat4x4_identity(MVP);
   mat4x4_translate(MVP, x, y, z);
}

// TODO: Fix to function correctly
void scale(unsigned int ShaderID, mat4x4 MVP)
{
   mat4x4_identity(MVP);
   //mat4x4_scale(MVP, MVP, x);
   mat4x4_scale_aniso(MVP, MVP, sx, sy, sz);
}

void transform(unsigned int ShaderID, mat4x4 MVP) 
{
   scale(ShaderID, MVP);
   translate(ShaderID, MVP);

   GLuint MatrixID = glGetUniformLocation(ShaderID, "transform");

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

   // Matrix coords for debugging
   int i,j;
   for(i=0; i<4; ++i) {
      for(j=0; j<4; ++j)
         printf("%f, ", MVP[i][j]);
      printf("\n");
   }

   // Render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // Input
      processInput(window.getHandle());

      // Rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);

      shader.use();

      transform(shader.shaderProgram, MVP);

      cube.draw();

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}