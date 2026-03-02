#include "transform.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <iostream>

Transform::Transform()
{
    this->m_ID = UUID();
    this->m_position = glm::vec3(0.0f);
    this->m_rotation = glm::vec3(0.0f);
    this->m_size = glm::vec3(1.0f);
}
Transform::~Transform()
{
    
}
//TODO: move m_model to transform
void Transform::Translate(glm::mat4* model, glm::vec3 delta_position)
{
    std::cout << "TEST TRANSLATE" << std::endl;
    this->m_position += delta_position;
    *model = glm::translate(*model, this->m_position);

    *model = glm::rotate(*model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    *model = glm::scale(*model, this->m_size);
}

void Transform::Rotate(glm::mat4* model, glm::vec3 delta_rotation)
{
    this->m_rotation += delta_rotation;
    *model = glm::translate(*model, this->m_position);

    *model = glm::rotate(*model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    *model = glm::scale(*model, this->m_size);
}

void Transform::Scale(glm::mat4* model, glm::vec3 delta_size)
{
    this->m_size *= delta_size;
    *model = glm::translate(*model, this->m_position);

    *model = glm::rotate(*model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    *model = glm::scale(*model, this->m_size);
}

void Transform::SetSize(glm::mat4* model, glm::vec3 size)
{
    this->m_size = size;
    *model = glm::translate(*model, this->m_position);

    *model = glm::rotate(*model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    *model = glm::rotate(*model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    *model = glm::scale(*model, this->m_size);
}