#pragma once

#include <glad/glad.h> 
#include "linmath.h"


typedef struct {
    vec3 position;
    vec3 color;
    vec2 textureCoordinate;
} Vertex;

class Cube {
public:
    Cube() {};
    ~Cube() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    };

    void init(Vertex *vertexData, unsigned int *indices);

    void draw();
private:
    Vertex vertexData;

    unsigned int texture;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};