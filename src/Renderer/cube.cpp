#include "cube.hpp"


void Cube::init(Vertex *vertexData, unsigned int *indices) {
    // Needs to be done only once!
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  
    glGenBuffers(1, &VBO);  
    glGenBuffers(1, &EBO);

    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);

    // Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}

void Cube::draw() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // We have to specify how OpenGL interprets the vertex data before rendering
    // Position attribute pointer
    glVertexAttribPointer(
        0,                  // attribute 0, must match the layout in the shader
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,                  // stride
        (void*)0            // array buffer offset
    );
    
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}