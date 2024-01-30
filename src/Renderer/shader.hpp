#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h> 

#include "common.h"


void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int ID);

class Shader {
public:
   Shader() = default;
   ~Shader() = default;

   void init(const char* vertexFilePath, const char* fragmentFilePath);   
   void enable();
   void disable();

   // utility uniform functions
    void setBool(const std::string& name, bool value) ;  
    void setInt(const std::string& name, int value);   
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, const mat4x4& mat);
    void setMat4(const std::string& name, mat4 mat);
    void enableAttribute(const std::string& name, int count, int stride, void* ptr);
    void disableAttribute(const std::string& name);
    void setTexture(const std::string& name, int index);

private:
   unsigned int ID;

};