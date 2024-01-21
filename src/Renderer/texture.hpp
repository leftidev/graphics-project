#pragma once

#include <glad/glad.h> 


class Texture
{
public:
    Texture();
    ~Texture() {};

    int getHandle() { return texture; };

private:
    unsigned int texture;
    
};
