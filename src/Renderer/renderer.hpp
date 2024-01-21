#pragma once

#include <glad/glad.h> 

#include "linmath.h"

#include "shader.hpp"
#include "texture.hpp"
#include "common.h"


class Renderer {
public:
    Renderer() {};
    ~Renderer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        //glDeleteBuffers(1, &EBO);
    };

    void init(Vertex *vertexData);

    void draw();
private:
    void render(Shader& shader);

    Texture m_texture{};

    Shader m_shader;

    unsigned int VAO;
    unsigned int VBO;
    //unsigned int EBO;
};