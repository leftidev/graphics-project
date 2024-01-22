#pragma once

#include <glad/glad.h> 

#include "common.h"



class Camera {
public:
    Camera();
    ~Camera();

    void init();

private:
    vec3 cameraPos {0.0f, 0.0f, 3.0f};
    vec3 cameraTarget {0.0f, 0.0f, 0.0f};
    vec3 cameraDirection{};
    vec3 cameraRight{};
    vec3 cameraUp{};
};