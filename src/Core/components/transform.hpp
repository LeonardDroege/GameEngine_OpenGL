#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer.hpp"
#include "../uuid.hpp"

class Transform
{
    public:
        Transform();
        ~Transform();

        void Translate(glm::vec3 delta_position, glm::mat4* model);
        void Rotate(glm::vec3 delta_rotation, glm::mat4* model);
        void Scale(glm::vec3 delta_size, glm::mat4* model);
        void SetSize(glm::vec3 size, glm::mat4* model);

        void ExecuteTransformation();

    private:
        UUID m_ID;

        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;
    
};

#endif