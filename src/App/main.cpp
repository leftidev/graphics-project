#include <stdio.h>

#include "Window.h"

// Create a very basic vertex shader in GLSL
// Give input vertex data in normalized device coordinates
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 Pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);\n"
    "}\0";

// Create a very basic fragment shader in GLSL
// Calculate the color output of pixels
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

// Check for compile-time errors on shader compilation
// TODO: Add check: which shader type?
void checkShaderCompileErrors(unsigned int shader)
{
   int  success;
   char infoLog[512];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

   if(!success)
   {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      fprintf(stderr, "SHADER ERROR COMPILATION: Shader compilation failed!\n %s", infoLog);
   }
}

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

   // First process of the graphics pipeline: vertex shader
   // Generate vertex array object
   unsigned int VAO;
   glGenVertexArrays(1, &VAO);  

   // Manage memory on the GPU via allocation of vertex buffer object (VBO)
   glBindVertexArray(VAO);
   unsigned int VBO;
   glGenBuffers(1, &VBO);  
   glBindBuffer(GL_ARRAY_BUFFER, VBO);  
   // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
   
   // Copy vertex data into buffer's memory:
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // For OpenGL to use the vertex shader, create a shader object and create the shader:
   unsigned int vertexShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);
   checkShaderCompileErrors(vertexShader);

   // Second process of the graphics pipeline: fragment shader
   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);
   checkShaderCompileErrors(fragmentShader);

   // Link both shader objects into a shader program, that can be used for rendering
   unsigned int shaderProgram;
   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   // Check linking of the shader program
   int success;
   char infoLog[512];
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      fprintf(stderr, "SHADER ERROR LINKING: Linking shader program failed!\n %s", infoLog);
   }

   // Every shader and rendering call after glUseProgram will now use the shaders
   glUseProgram(shaderProgram);

   // Delete shader objects once they're linked into the program object
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);  

   // We have to specify how OpenGL interprets the vertex data before rendering
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0); 
   // Vertex attribute takes its data from memory managed by a VBO
   // Which VBO it takes the data from is determined by VBO currently bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer


   // render loop
   while (!glfwWindowShouldClose(window.getHandle())) {
      // input
      processInput(window.getHandle());

      // rendering commands
      glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
   
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      // check and call events and swap the buffers
      glfwSwapBuffers(window.getHandle());
      glfwPollEvents();
   }

   glfwDestroyWindow(window.getHandle());
   glfwTerminate();

   return 0;
}