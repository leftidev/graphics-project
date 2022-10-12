#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h> 

#include "linmath.h"

void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int ID);

class Shader {
public:
   Shader() = default;
   ~Shader() = default;

   void init(const char *vertexFilePath, const char *fragmentFilePath);   
   void use();

   // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

   unsigned int ID;
};