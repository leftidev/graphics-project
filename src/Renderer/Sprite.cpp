#include "Sprite.h"

void Sprite::init() {
    vertexData[0] = {-0.5f, -0.5f, 0.0f};
    vertexData[1] = {0.5f, -0.5f, 0.0f};
    vertexData[2] = {0.0f, 0.5f, 0.0f};
        // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  

    glGenBuffers(1, &VBO);  
    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into buffer's memory:
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
}

void Sprite::draw() {
    // Manage memory on the GPU via allocation of vertex buffer object (VBO)
    glBindVertexArray(VAO);

    // We have to specify how OpenGL interprets the vertex data before rendering
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    // Vertex attribute takes its data from memory managed by a VBO
    // Which VBO it takes the data from is determined by VBO currently bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer
    glDrawArrays(GL_TRIANGLES, 0, 3);
}