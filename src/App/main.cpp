#include <stdio.h>

#include "window.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "cube.hpp"
#include "camera.hpp"


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

Camera cam;


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
   //const float cameraSpeed = 0.05f; // adjust accordingly

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      //cam.cameraPos += cam.cameraSpeed * cam.cameraFront;
      //vec3_mul_inner(cam.cameraSpeed, cam.cameraFront);
      //vec3_scale(&cam.cameraFront[2], &cam.cameraFront[2], cam.cameraSpeed);
      vec3_sub(&cam.cameraPos[0], &cam.cameraPos[0], &cam.cameraSpeed);      
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
         //vec3_scale(&cam.cameraFront[2], &cam.cameraFront[2], cam.cameraSpeed);
         vec3_add(&cam.cameraPos[0], &cam.cameraPos[0], &cam.cameraSpeed);
      /*
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
   {
      vec3_mul_cross(cam.cameraRight, cam.cameraFront, cam.cameraUp);
      vec3_norm(cam.cameraRight, cam.cameraRight);
      cam.cameraRight * cam.cameraSpeed;
   }

   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cam.cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
*/
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

   Renderer renderer;

   // Renderables
   Cube cube;

   
   unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
   };

   // Render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // Input
      processInput(window.getHandle());

      // Rendering commands
      glClearColor(0.2f, 1.0f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render
      renderer.draw(cube, cam);

      // Check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}