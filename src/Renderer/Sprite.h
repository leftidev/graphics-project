#pragma once

#include <glad/glad.h> 

struct Position {
    float x;
    float y;
};

struct Vertex {
   float z;
   float x;
   float y;
};

class Sprite {
public:
    Sprite() {};
    ~Sprite() {};

    void init();
    void draw();
private:
    Position position;
    Vertex vertexData[3];

    unsigned int VAO;
    unsigned int VBO;
};