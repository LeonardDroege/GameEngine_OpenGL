#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.hpp"

class Triangle : public Object
{
    public:
        Triangle(glm::mat4* view_matrix, glm::mat4* projection_matrix) : Object(view_matrix, projection_matrix) { }
        ~Triangle() { }
        
};

#endif