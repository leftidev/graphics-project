#include "renderer.hpp"

#include "GLFW/glfw3.h"

const float RATIO = 800 / (float) 600;


void Renderer::init()
{
    m_shader.init("../data/shaders/cube.vs", "../data/shaders/cube.fs");
    m_texture.init("../data/images/container.jpg");
}

void Renderer::draw(Renderable& r, Camera& cam) 
{
    m_shader.enable();

    Vec3 cubePositions[] = {
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

    //mat4x4 proj, model;
    //mat4x4 model;
    mat4 model = mat4_id();
    //mat4_id(model);
    // Create transformations
    mat4x4_identity(cam.view);
   // mat4x4_identity(proj);

    //mat4x4_perspective(proj, 45.0f, RATIO, 0.1f, 100.0f);
    mat4 proj; 
    mat4_perspective_two(proj, 45.0f, 0.1f, 100.0f, RATIO);

    //mat4 proj = mat4_perspective(0.785398163, 0.1, 512.0, RATIO);
    //mat4x4_translate(view, 0.0f, 0.0f, -13.0f);
    
    //vec3 eye = {0.0f, 0.0f, 3.0f};
    //vec3 center = {0.0f, 0.0f, 0.0f};
    //vec3 up = {0.0f, 1.0f, 0.0f};
    //mat4x4_look_at(view, eye, center, up);

    // Create a camera rotating around the scene
    //const float radius = 10.0f;
    //float camX = sin(glfwGetTime()) * radius;
    //float camZ = cos(glfwGetTime()) * radius;
    //vec3 eyeRotate = {camX, 0.0f, camZ};
    
    //mat4x4_look_at(view, eyeRotate, center, up);

    vec3 temp{};
    // Ensure the camera keeps looking at target direction when moving
    vec3_add(temp, cam.cameraPos, cam.cameraFront);
    mat4x4_look_at(cam.view, cam.cameraPos, temp, cam.cameraUp);

    // Retrieve matrix uniform locations and pass them to shaders
    m_shader.setMat4("projection", proj);
    m_shader.setMat4("view", cam.view);
    // NOTE: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

    // Test transformations
    //mat4x4_rotate_X(model, model, (float) glfwGetTime());
    //mat4x4_rotate_Y(model, model, (float) glfwGetTime());
    //mat4x4_rotate_Z(model, model, (float) glfwGetTime());
    //mat4x4_scale_aniso(model, model, sz, sz, sz);
    //mat4x4_translate(view, x, y, -3.0f);
    //mat4x4_ortho(proj, -RATIO, RATIO, -1.f, 1.f, 1.f, -1.f);

    
    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        model = mat4_mul_mat4(mat4_rotation_x((float)glfwGetTime()), mat4_rotation_y((float)glfwGetTime()));
        model = mat4_mul_mat4(mat4_rotation_z((float)glfwGetTime()), model);
        mat4_translation(model, cubePositions[i]);

        m_shader.setMat4("model", model);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, m_texture.getHandle());

        glBindVertexArray(r.vertexVAO);
        glBindBuffer(GL_ARRAY_BUFFER, r.vertexVBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        m_shader.enableAttribute("aPos", 3, 5, (void*)0);
        m_shader.enableAttribute("aTexCoord", 2, 5, (void*)(sizeof(float) * 3));

        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        m_shader.disableAttribute("aPos");
        m_shader.disableAttribute("aTexCoord");

        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    m_shader.disable();
}