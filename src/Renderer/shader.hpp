#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h> 

#include "linmath.h"

void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int shaderProgram);

class Shader {
public:
   Shader() = default;
   ~Shader() = default;

   void init(const char *vertex_file_path, const char *fragment_file_path);   
   void use();

   unsigned int shaderProgram;

private:
};