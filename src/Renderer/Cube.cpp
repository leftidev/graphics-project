#include "Cube.h"

// First test
void Cube::init(const Vertex (&vertexData)[3]) {
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

// Testing 2
void Cube::init2(Vertex *vertexData) {
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  

    glGenBuffers(1, &VBO);  
    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into buffer's memory:
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, vertexData, GL_STATIC_DRAW);

    // Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Testing 3
void Cube::init3(const Vertex &vertexData) {
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  

    glGenBuffers(1, &VBO);  
    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data into buffer's memory:
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &vertexData, GL_STATIC_DRAW);

    // Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw() {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0); 

    // We have to specify how OpenGL interprets the vertex data before rendering
    // Position attribute pointer
    glVertexAttribPointer(
        0,                  // attribute 0, must match the layout in the shader
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized
        0,  // stride
        (void*)0            // array buffer offset
    );
    
    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}