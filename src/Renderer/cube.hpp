#pragma once

#include <glad/glad.h> 

#include "linmath.h"

#include "shader.hpp"
#include "common.h"


class Cube {
public:
    Cube() {};
    ~Cube() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        //glDeleteBuffers(1, &EBO);
    };

    void init(Vertex *vertexData);

    void draw(Shader& shader);
private:
    //Vertex vertexData;

    unsigned int texture;
    unsigned int VAO;
    unsigned int VBO;
    //unsigned int EBO;
};