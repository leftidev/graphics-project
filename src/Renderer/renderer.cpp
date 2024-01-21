#include "Renderer.hpp"

#include "GLFW/glfw3.h"

const float RATIO = 800 / (float) 600;

void Renderer::init(Vertex *vertexData) 
{
    //shader.init("../data/shaders/texture_vertex.vs", "../data/shaders/texture_fragment.fs");
    //shader.init("../data/shaders/uniform_vertex.vs", "../data/shaders/uniform_fragment.fs");
    m_shader.init("../data/shaders/cube.vs", "../data/shaders/cube.fs");

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

void Renderer::draw() {

    vec3 cubePositions[] = {
      { 0.0f,  0.0f,  0.0f},
      { 2.0f,  5.0f, -15.0f},
      {-1.5f, -2.2f, -2.5f},
      {-3.8f, -2.0f, -12.3f},
      { 2.4f, -0.4f, -3.5f},
      {-1.7f,  3.0f, -7.5f},
      { 1.3f, -2.0f, -2.5f},
      { 1.5f,  2.0f, -2.5f},
      { 1.5f,  0.2f, -1.5f},
      {-1.3f,  1.0f, -1.5f}
   };

    mat4x4 proj, view, model;
    // Create transformations
    mat4x4_identity(view);
    mat4x4_identity(proj);

    mat4x4_perspective(proj, 45.0f, RATIO, 0.1f, 100.0f);
    mat4x4_translate(view, 0.0f, 0.0f, -3.0f);

    // Retrieve matrix uniform locations and pass them to shaders
    m_shader.setMat4("projection", proj);
    m_shader.setMat4("view", view);
    // NOTE: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

    // Test transformations
    //mat4x4_rotate_X(model, model, (float) glfwGetTime());
    //mat4x4_rotate_Y(model, model, (float) glfwGetTime());
    //mat4x4_rotate_Z(model, model, (float) glfwGetTime());
    //mat4x4_scale_aniso(model, model, sz, sz, sz);
    //mat4x4_translate(view, x, y, -3.0f);
    //mat4x4_ortho(proj, -RATIO, RATIO, -1.f, 1.f, 1.f, -1.f);

    m_shader.enable();
    for (unsigned int i = 0; i < 10; i++)
    {
    // calculate the model matrix for each object and pass it to shader before drawing
    mat4x4_identity(model);

    mat4x4_translate(model, cubePositions[i][0], cubePositions[i][1], cubePositions[i][2]);
    mat4x4_rotate_X(model, model, (float) glfwGetTime());
    mat4x4_rotate_Y(model, model, (float) glfwGetTime());
    mat4x4_rotate_Z(model, model, (float) glfwGetTime());

    m_shader.setMat4("model", model);

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
    m_shader.enableAttribute("aPos", 3, 5, (void*)0);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // texture coord attribute
    m_shader.enableAttribute("aTexCoord", 2, 5, (void*)(sizeof(float) * 3));

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

    m_shader.disableAttribute("aPos");
    m_shader.disableAttribute("aTexCoord");
    //glDisableVertexAttribArray(1);
    //glDisableVertexAttribArray(0);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    }
}

void Renderer::render(Shader& shader)
{
    /*
     Render process:

    1. Create and enable shader
    2. Set shader attributes
    3. Get renderable handle
        - Get vertices / material / triangles from renderable
        - Renderable has function for creating new:
            1. glGenBuffers
            2. Get/create vertices
            3. glBindBuffer(GL_ARRAY_BUFFER) from vertices
            4. glBufferData
            4. (optional) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER)
            4. glBufferData
            5. glBindBuffer(0) for both

    4. Set texture in shader
    4. GlBindBuffer(vertices)
    5. Enable shader attributes (Position, Texture coords)
    6. glDrawArrays / glDrawElements
    7. Disable shader attributes
    8. glBindBuffer(0)
    9. Disable shader
    */


}