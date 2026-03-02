#ifndef GLOBAL_H
#define GLOBAL_H

#include <glm/glm.hpp>

static double FPS = 180.0;

static constexpr glm::vec3 DIRECTION_UP(0.0f, 1.0f, 0.0f);
static constexpr glm::vec3 DIRECTION_LEFT(-1.0f, 0.0f, 0.0f);
static constexpr glm::vec3 DIRECTION_DOWN(0.0f, -1.0f, 0.0f);
static constexpr glm::vec3 DIRECTION_RIGHT(1.0f, 0.0f, 0.0f);

struct Color
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif