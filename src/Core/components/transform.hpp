#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../uuid.hpp"

class Transform
{
    public:
        Transform();
        ~Transform();

        void Translate(glm::mat4* model, glm::vec3 delta_position);
        void Rotate(glm::mat4* model, glm::vec3 delta_rotation);
        void Scale(glm::mat4* model, glm::vec3 delta_size);
        void SetSize(glm::mat4* model, glm::vec3 size);

        void ExecuteTransformation();

    private:
        UUID m_ID;

        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;
    
};

#endif