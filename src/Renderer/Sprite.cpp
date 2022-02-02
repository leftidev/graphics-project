#include "Sprite.h"

void Sprite::init(const Vertex (& vertexData)[3]) {
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  

    glGenBuffers(1, &VBO);  
    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into buffer's memory:
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0); 

    // We have to specify how OpenGL interprets the vertex data before rendering
    // Position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}