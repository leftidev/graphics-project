#include "cube.hpp"


// Create the implementation of stb_image by including it
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb/stb_image.h"

void Cube::init(Vertex *vertexData) {
    // Needs to be done only once!
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &VAO);  
    glGenBuffers(1, &VBO);  
    //glGenBuffers(1, &EBO);

    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertexData) * 36, vertexData, GL_STATIC_DRAW);
/*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);
*/


    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}

void Cube::draw(Shader& shader) {
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, m_texture.getHandle());

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
/*
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
*/

    // position attribute
    shader.enableAttribute("aPos", 3, 5, (void*)0);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // texture coord attribute
    shader.enableAttribute("aTexCoord", 2, 5, (void*)(sizeof(float) * 3));

    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

/*
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
  */  
    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //glDisableVertexAttribArray(2);

    shader.disableAttribute("aPos");
    shader.disableAttribute("aTexCoord");
    //glDisableVertexAttribArray(1);
    //glDisableVertexAttribArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}