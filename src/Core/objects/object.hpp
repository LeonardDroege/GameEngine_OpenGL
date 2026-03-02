#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

#include "../uuid.hpp"
#include "../graphics/shader.hpp"
#include "../components/renderer.hpp"
#include "../components/transform.hpp"

class Object
{

    public:
        Object(glm::mat4* view_matrix, glm::mat4* projection_matrix);
        ~Object();

        void Draw(Shader& shader);

        void Translate(glm::vec3 delta_position);
        void Rotate(glm::vec3 delta_rotation);
        void Scale(glm::vec3 delta_size);
        void SetSize(glm::vec3 size);

    protected:
        UUID m_ID;

        Renderer m_renderer;
        Transform m_transform;
        glm::mat4 m_model;

};

#endif