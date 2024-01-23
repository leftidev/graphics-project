#pragma once

#include <glad/glad.h> 

#include "common.h"



class Camera {
public:
    Camera();
    ~Camera();

    void init();

    mat4x4 view;
    const float cameraSpeed = 0.05f;
    //vec3 cameraSpeed {0.05f, 0.05f, 0.05f};
    vec3 cameraPos {0.0f, 0.0f, 3.0f};
    vec3 cameraTarget {0.0f, 0.0f, 0.0f};
    vec3 cameraDirection{};
    vec3 cameraRight{};
    vec3 cameraFront {0.0f, 0.0f, -1.0f};
    vec3 cameraUp {0.0f, 1.0f, 0.0f};
private:


};