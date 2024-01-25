#pragma once

#include <glad/glad.h> 

#include "linmath.h"

#include "shader.hpp"
#include "texture.hpp"
#include "renderable.hpp"
#include "camera.hpp"

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void init();

    void draw(Renderable& r, Camera& cam);
    
private:
    Texture m_texture;
    Shader m_shader;
};