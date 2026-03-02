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
        Transform(glm::mat4* view_matrix, glm::mat4* projection_matrix);
        ~Transform();

        void Translate(glm::vec3 delta_position);
        void Rotate(glm::vec3 delta_rotation);
        void Scale(glm::vec3 delta_size);
        void SetSize(glm::vec3 size);

        void Render(Shader& shader);

        inline Renderer& GetRenderer() { return this->m_renderer; }

        void ExecuteTransformation();

    private:
        inline void reset_model() { this->m_model = glm::mat4(1.0f); }

    private:
        UUID m_ID;

        Renderer m_renderer;

        glm::mat4 m_model;
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_size;
    
};

#endif