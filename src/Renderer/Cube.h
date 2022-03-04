#pragma once

#include <glad/glad.h> 
#include "linmath.h"


typedef struct {
    vec3 point;
} Vertex;

class Cube {
public:
    Cube() {};
    ~Cube() {};

    void init(Vertex *vertexData);
    void init(const Vertex &vertexData);

    void draw();
private:
    Vertex vertexData;

    unsigned int VAO;
    unsigned int VBO;
};