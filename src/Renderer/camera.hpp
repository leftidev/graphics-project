#pragma once

#include <glad/glad.h> 

#include "common.h"




class Camera {
public:
    Camera() = default;
    ~Camera() = default;

    void init();

    mat4x4 view;
    const float cameraSpeed = 0.05f;
    //const vec3 cameraSpeed {0.00f, 0.00f, 0.05f};
    vec3 cameraPos {0.0f, 0.0f, 3.0f};
    vec3 cameraTarget {0.0f, 0.0f, 0.0f};
    vec3 cameraDirection{};
    vec3 cameraRight{};
    vec3 cameraLeft{};
    vec3 cameraFront {0.0f, 0.0f, -1.0f};
    vec3 cameraUp {0.0f, 1.0f, 0.0f};
    Vec3 target = Vec3_zero();
    Vec3 pos = Vec3_new(0, 0, 3);

};

inline Vec3 camera_direction(Camera& c) {
  return Vec3_normalize(Vec3_sub(c.target, c.pos));
}