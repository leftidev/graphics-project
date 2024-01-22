#pragma once


class Renderable {
public:
    virtual ~Renderable() {} // ensure derived dtors are virtual

    unsigned int vertexVBO;
    unsigned int vertexVAO;
};