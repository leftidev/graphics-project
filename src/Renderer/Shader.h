#pragma once

#include <stdio.h>

#include <glad/glad.h> 

#include "linmath.h"

void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int shaderProgram);

class Shader {
public:
   Shader() {};
   ~Shader() {};

   void init();   
   void use();

   unsigned int shaderProgram;

private:
};