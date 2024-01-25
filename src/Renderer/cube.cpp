#include "cube.hpp"


Cube::~Cube() 
{
    glDeleteVertexArrays(1, &vertexVAO);
    glDeleteBuffers(1, &vertexVBO);
    //glDeleteBuffers(1, &EBO);
}

void Cube::init() 
{
    // Needs to be done only once!
    // First process of the graphics pipeline: vertex shader
    // Generate vertex array object
    glGenVertexArrays(1, &vertexVAO);  
    glGenBuffers(1, &vertexVBO);  
    //glGenBuffers(1, &EBO);

    Vertex m_vertexData[] = {
        {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
        {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
        { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        {  0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        {  0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        { -0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

        { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        { -0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        { -0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

        {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        {  0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        {  0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        {  0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        {  0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
        {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        { -0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
        {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        { -0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
        { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };

    // Now any buffer calls we make on GL_ARRAY_BUFFER target will be used to configure currently bound buffer VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*m_vertexData) * 36, &m_vertexData, GL_STATIC_DRAW);
/*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);
*/
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
}