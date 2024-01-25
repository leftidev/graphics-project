#pragma once

#include <glad/glad.h> 

#include "renderable.hpp"
#include "common.h"


class Cube: public Renderable {
public:
    Cube() = default;
    ~Cube();

    void init();
};