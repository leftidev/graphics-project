#pragma once

#include <stdio.h>

#include <glad/glad.h> 

void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int shaderProgram);

class Shader {
public:
   Shader() {};
   ~Shader() {};

   void init();   
   void use();

private:
   unsigned int shaderProgram;
};