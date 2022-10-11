#include "shader.hpp"


// Create a very basic vertex shader in GLSL
// Give input vertex data in normalized device coordinates
const char* vertexShaderSource3 = "#version 330 core\n"
    "layout (location = 0) in vec3 Pos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);\n"
    "}\0";

// Testing
const char* vertexShaderSource2 = "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "uniform mat4 MVP;\n"
    "void main()\n"
    "{\n"
    "   vec4 v = vec4(vertexPosition_modelspace,1);\n"
    "   gl_Position = MVP * v;\n"
    "}\0";

// Testing 2
const char* vertexShaderSource = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0f);\n"
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

void Shader::init(const char *vertexFilePath, const char *fragmentFilePath) {
   // For OpenGL to use the vertex shader, create a shader object and create the shader:
   unsigned int vertexShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);

   // Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if(vertexShaderStream.is_open())
   {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
   else
   {
      printf("Unable to open %s. Are you in the right directory ?\n", vertexFilePath);
	}

   // Compile Vertex Shader
	printf("Compiling vertex shader : %s\n", vertexFilePath);
   char const *vertexSourcePointer = vertexShaderCode.c_str();
   glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
   glCompileShader(vertexShader);

   checkShaderCompileErrors(vertexShader);
   
   // Second process of the graphics pipeline: fragment shader
   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}

   // Compile Fragment Shader
	printf("Compiling fragment shader : %s\n", fragmentFilePath);
   char const *fragmentSourcePointer = fragmentShaderCode.c_str();
   glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
   glCompileShader(fragmentShader);

   checkShaderCompileErrors(fragmentShader);

   // Link both shader objects into a shader program, that can be used for rendering
   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   checkShaderLinkErrors(shaderProgram);

   // Detach shaders
   glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

   // Delete shader objects once they're linked into the program object
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);  
}

void Shader::use() {
   // Every shader and rendering call after glUseProgram will now use the shaders
   glUseProgram(shaderProgram);
}