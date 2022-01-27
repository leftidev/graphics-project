#pragma once

#include <stdio.h>

#include <glad/glad.h> 

void checkShaderCompileErrors(unsigned int shader);
void checkShaderLinkErrors(unsigned int shaderProgram);

struct Vertex {
   float z;
   float x;
   float y;
};

struct Triangle {
   Vertex vertices[3];
};

class Shader {
public:
    Shader() {};
    ~Shader() {};
    void init(float (&vertices)[9]);
    void init2(Vertex (&vertexData)[3]);

    unsigned int VAO;
    unsigned int shaderProgram;
private:

};