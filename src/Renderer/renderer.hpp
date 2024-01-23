#pragma once

#include <glad/glad.h> 

#include "linmath.h"

#include "shader.hpp"
#include "texture.hpp"
#include "renderable.hpp"
#include "camera.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer() {}

    void draw(Renderable* r, Camera* cam);
private:
    Texture m_texture;
    Shader m_shader;
};