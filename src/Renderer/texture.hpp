#pragma once

#include <glad/glad.h> 

#include <string>


class Texture
{
public:
   Texture() = default;
   ~Texture() = default;

    void init(const std::string& path);

    int getHandle() { return texture; };

private:
    unsigned int texture;
    
};
