#include "shader.hpp"

   
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
      std::cerr << "ERROR: Compiling shader program failed. Info: " << infoLog << std::endl;
   }
}

// Check for compile-time errors on shader linking
void checkShaderLinkErrors(unsigned int shader)
{
   int  success;
   char infoLog[512];
   glGetProgramiv(shader, GL_LINK_STATUS, &success);

   if(!success)
   {
      glGetProgramInfoLog(shader, 512, NULL, infoLog);
      std::cerr << "ERROR: Linking shader program failed. Info: " << infoLog << std::endl;
   }
}

void Shader::init(const char* vertexFilePath, const char* fragmentFilePath) 
{
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
    std::cout << "Compiling vertex shader: " << vertexFilePath << std::endl;
    char const *vertexSourcePointer = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader);

    // Compile Fragment Shader
    std::cout << "Compiling fragment shader: " << fragmentFilePath << std::endl;
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

void Shader::enable() 
{
   glUseProgram(ID);
}

void Shader::disable() 
{
    glActiveTexture(GL_TEXTURE0);   
    glUseProgram(0);
}

void Shader::enableAttribute(const std::string& name, int count, int stride, void* ptr)
{
    GLint attr = glGetAttribLocation(ID, name.c_str());
    if (attr == -1) 
    {
        std::cerr << "Shader has no attribute called " << name << std::endl;
    } 
    else
    {
        glEnableVertexAttribArray(attr);  
        glVertexAttribPointer(attr, count, GL_FLOAT, GL_FALSE, sizeof(float) * stride, ptr);
    }
}

void Shader::disableAttribute(const std::string& name)
{
    GLint attr = glGetAttribLocation(ID, name.c_str());
    if(attr == -1)
    {
        std::cerr << "Shader has no attribute called " << name << std::endl;
    } 
    else 
    {
        glDisableVertexAttribArray(attr);  
    }
}

void Shader::setTexture(const std::string& name, int index)
{
    GLint location = glGetUniformLocation(ID, name.c_str());

    if(location == -1) 
    {
        std::cerr << "Shader has no uniform called " << name << std::endl;
    } 
    else 
    {
        glActiveTexture(GL_TEXTURE0 + index);

        // glBindTexture with correct parameters
        //glBindTexture(texture_type(asset_hndl_ptr(&t)), texture_handle(asset_hndl_ptr(&t)));
        glUniform1i(location, index);
    }
}

void Shader::setBool(const std::string& name, bool value)
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string& name, int value)
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string& name, float value)
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 
void Shader::setMat4(const std::string& name, const mat4x4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

/*
// ------------------------------------------------------------------------
void setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
*/
// ------------------------------------------------------------------------
