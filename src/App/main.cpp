#include <stdio.h>

#include "window.hpp"
#include "shader.hpp"
#include "renderer.hpp"


enum PolygonMode {
    LINE,
    FILL
};

// GLOBAL VARIABLES (For testing purposes)
static float x = 0.0f;
static float y = 0.0f;
static float z = 0.0f;

static float sx = 1.0f;
static float sy = 1.0f;
static float sz = 1.0f;

static PolygonMode mode = FILL;


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
   if (key == GLFW_KEY_C && action == GLFW_PRESS)
   {
      if(mode == FILL)
      {
         mode = LINE;
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         printf("Wireframe mode on\n");
      }
      else
      {
         mode = FILL;
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         printf("Wireframe mode off\n");
      }
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
   glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void translate(unsigned int ShaderID, mat4x4 MVP)
{
   //mat4x4_identity(MVP);
   mat4x4_translate(MVP, x, y, z);
}

// TODO: Fix to function correctly
void scale(unsigned int ShaderID, mat4x4 MVP)
{
   //mat4x4_identity(MVP);
   mat4x4_scale(MVP, MVP, sz);
   //mat4x4_scale_aniso(MVP, MVP, sx, sy, sz);
}

void transform(unsigned int ShaderID, mat4x4 MVP) 
{
   //scale(ShaderID, MVP);
   //translate(ShaderID, MVP);

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
   window.init(800, 600, "Hello");

   // Set callbacks
   glfwSetKeyCallback(window.getHandle(), keyCallback);
   glfwSetMouseButtonCallback(window.getHandle(), mouseButtonCallback);
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

   // configure global opengl state
   // -----------------------------
   glEnable(GL_DEPTH_TEST);

   unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
   };


   Vertex vertices[] = {
   {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
   {  0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
   {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
   {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
   { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
   { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

   { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
   {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
   {  0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
   {  0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
   { -0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
   { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

   { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
   { -0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
   { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
   { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
   { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
   { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

   {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
   {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
   {  0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
   {  0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
   {  0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
   {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

   { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
   {  0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
   {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
   {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
   { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
   { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

   { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
   {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
   {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
   {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
   { -0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
   { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
};


// world space positions of our cubes
   vec3 cubePositions[] = {
      { 0.0f,  0.0f,  0.0f},
      { 2.0f,  5.0f, -15.0f},
      {-1.5f, -2.2f, -2.5f},
      {-3.8f, -2.0f, -12.3f},
      { 2.4f, -0.4f, -3.5f},
      {-1.7f,  3.0f, -7.5f},
      { 1.3f, -2.0f, -2.5f},
      { 1.5f,  2.0f, -2.5f},
      { 1.5f,  0.2f, -1.5f},
      {-1.3f,  1.0f, -1.5f}
   };

   Renderer cubes;
   cubes.init(vertices);

   // Render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // Input
      processInput(window.getHandle());

      // Rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      cubes.draw();

      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}