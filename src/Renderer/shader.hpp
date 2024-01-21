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
   void enable();
   void disable();

   // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string& name, const mat4x4& mat) const;
    void enableAttribute(const std::string &name, int count, int stride, void* ptr) const;
    void disableAttribute(const std::string& name) const;

private:
   int getHandle() { return ID; };

   unsigned int ID;
};