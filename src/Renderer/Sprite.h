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

    void init(const Vertex (& vertexData)[3]);
    void draw();
private:
    Position position;
    Vertex* m_vertexData;

    unsigned int VAO;
    unsigned int VBO;
};