#include <stdio.h>

#include "window.hpp"
#include "shader.hpp"
#include "cube.hpp"
//#include "rectangle.hpp"

const unsigned int WINDOWWIDTH = 800;
const unsigned int WINDOWHEIGHT = 600;
const float RATIO = WINDOWWIDTH / (float) WINDOWHEIGHT;

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
   window.init(WINDOWWIDTH, WINDOWHEIGHT, "Hello");

   // Set callbacks
   glfwSetKeyCallback(window.getHandle(), keyCallback);
   glfwSetMouseButtonCallback(window.getHandle(), mouseButtonCallback);
   glfwSetFramebufferSizeCallback(window.getHandle(), framebufferSizeCallback);

   // configure global opengl state
   // -----------------------------
   glEnable(GL_DEPTH_TEST);


   Shader shader;
   //shader.init("../data/shaders/texture_vertex.vs", "../data/shaders/texture_fragment.fs");
   //shader.init("../data/shaders/uniform_vertex.vs", "../data/shaders/uniform_fragment.fs");
   shader.init("../data/shaders/cube.vs", "../data/shaders/cube.fs");
   

   // Cube vertex data
   /*
   Vertex vertices[] = {
      // positions          // colors           // texture coords
      { 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f},   // top right
      { 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f},   // bottom right
      {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f},   // bottom left
      {-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f}    // top left 
   };
*/
   unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
   };

   //Rectangle rect;
   //rect.init(vertices, indices);


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

   Cube cubes;
   cubes.init(vertices);

   // Model View Projection matrix is a handy tool to separate transformations cleanly.
   // Model matrix: translation*rotation*scale, ORDER MATTERS. 
   // Something that doesn’t move will be at the center of the world.
   /*
      ModelViewProjection : multiplication of our 3 matrices
      mvp = Projection * View * Model; 
   */

   mat4x4 proj, view, model;

   
   // Render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // Input
      processInput(window.getHandle());

      // Rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Create transformations
      mat4x4_identity(view);
      mat4x4_identity(proj);

      mat4x4_perspective(proj, 45.0f, RATIO, 0.1f, 100.0f);
      mat4x4_translate(view, 0.0f, 0.0f, -3.0f);

      // Retrieve matrix uniform locations and pass them to shaders
      shader.setMat4("projection", proj);
      shader.setMat4("view", view);
      // NOTE: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

      // Test transformations
      //mat4x4_rotate_X(model, model, (float) glfwGetTime());
      //mat4x4_rotate_Y(model, model, (float) glfwGetTime());
      //mat4x4_rotate_Z(model, model, (float) glfwGetTime());
      //mat4x4_scale_aniso(model, model, sz, sz, sz);
      //mat4x4_translate(view, x, y, -3.0f);
      //mat4x4_ortho(proj, -RATIO, RATIO, -1.f, 1.f, 1.f, -1.f);

      shader.enable();
      for (unsigned int i = 0; i < 10; i++)
      {
         // calculate the model matrix for each object and pass it to shader before drawing
         mat4x4_identity(model);

         mat4x4_translate(model, cubePositions[i][0], cubePositions[i][1], cubePositions[i][2]);
         mat4x4_rotate_X(model, model, (float) glfwGetTime());
         mat4x4_rotate_Y(model, model, (float) glfwGetTime());
         mat4x4_rotate_Z(model, model, (float) glfwGetTime());

         shader.setMat4("model", model);

         cubes.draw(shader);
      }


      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}