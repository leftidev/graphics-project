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
void checkShaderLinkErrors(unsigned int ID)
{
   int  success;
   char infoLog[512];
   glGetProgramiv(ID, GL_LINK_STATUS, &success);

   if(!success)
   {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      fprintf(stderr, "SHADER ERROR LINKING: Linking shader program failed!\n %s", infoLog);
   }
}

void Shader::init(const char *vertexFilePath, const char *fragmentFilePath) {
   // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexFilePath);
        fShaderFile.open(fragmentFilePath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        printf("SHADER ERROR: File not read successfully.");
    }

   unsigned int vertexShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   
   // Compile Vertex Shader
	printf("Compiling vertex shader : %s\n", vertexFilePath);
   char const *vertexSourcePointer = vertexCode.c_str();
   glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
   glCompileShader(vertexShader);
   checkShaderCompileErrors(vertexShader);

   // Compile Fragment Shader
	printf("Compiling fragment shader : %s\n", fragmentFilePath);
   char const *fragmentSourcePointer = fragmentCode.c_str();
   glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
   glCompileShader(fragmentShader);
   checkShaderCompileErrors(fragmentShader);

   // Link both shader objects into a shader program, that can be used for rendering
   ID = glCreateProgram();
   glAttachShader(ID, vertexShader);
   glAttachShader(ID, fragmentShader);
   glLinkProgram(ID);

   checkShaderLinkErrors(ID);

   // Detach shaders
   glDetachShader(ID, vertexShader);
	glDetachShader(ID, fragmentShader);

   // Delete shader objects once they're linked into the program object
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);  
}

void Shader::use() {
   // Every shader and rendering call after glUseProgram will now use the shaders
   glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 