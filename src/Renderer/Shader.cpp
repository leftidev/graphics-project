#include "Shader.h"

// Create a very basic vertex shader in GLSL
// Give input vertex data in normalized device coordinates
const char* vertexShaderSource = "#version 330 core\n"
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

// Check for compile-time errors on shader linking
void checkShaderLinkErrors(unsigned int shaderProgram)
{
   int  success;
   char infoLog[512];
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

   if(!success)
   {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      fprintf(stderr, "SHADER ERROR LINKING: Linking shader program failed!\n %s", infoLog);
   }
}

void Shader::init() {
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
   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   checkShaderLinkErrors(shaderProgram);

   // Delete shader objects once they're linked into the program object
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);  
}

void Shader::use() {
   // Every shader and rendering call after glUseProgram will now use the shaders
   glUseProgram(shaderProgram);
}