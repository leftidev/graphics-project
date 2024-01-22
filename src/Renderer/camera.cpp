#include "camera.hpp"

Camera::Camera() 
{
    // Camera direction
    // Subtracting the camera position vector from the scene's origin vector (cameraTarget) results in the camera direction vector.
    vec3_sub(cameraDirection, cameraPos, cameraTarget);
    vec3_norm(cameraDirection, cameraDirection);

    // Right axis
    // To get the right vector we specify an up vector that points upwards (in world space). Then we do a cross product on the up vector and the camera direction vector.
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3_mul_cross(cameraRight, up, cameraDirection);
    vec3_norm(cameraRight, cameraRight);

    // Up axis
    // Retrieving the vector that points to the camera's positive y-axis is relatively easy: we take the cross product of the right and direction vector.
    vec3_mul_cross(cameraUp, cameraDirection, cameraRight);
    // Using these camera vectors we can now create a LookAt matrix that proves very useful for creating a camera.
}

Camera::~Camera() 
{

}

void Camera::init() 
{

}