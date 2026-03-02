#include "transform.hpp"
#include "glm/ext/matrix_transform.hpp"

Transform::Transform(glm::mat4* view_matrix, glm::mat4* projection_matrix) : m_renderer(Renderer(view_matrix, projection_matrix, Color {255, 200, 100, 50}))
{
    this->m_ID = UUID();
    this->m_model = glm::mat4(1.0f);
    this->m_position = glm::vec3(0.0f);
    this->m_rotation = glm::vec3(0.0f);
    this->m_size = glm::vec3(1.0f);
}
Transform::~Transform()
{
    
}

void Transform::Translate(glm::vec3 delta_position)
{
    this->reset_model();
    this->m_position += delta_position;
    this->m_model = glm::translate(this->m_model, this->m_position);

    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    this->m_model = glm::scale(this->m_model, this->m_size);
}

void Transform::Rotate(glm::vec3 delta_rotation)
{
    this->reset_model();
    this->m_rotation += delta_rotation;
    this->m_model = glm::translate(this->m_model, this->m_position);

    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    this->m_model = glm::scale(this->m_model, this->m_size);
}

void Transform::Scale(glm::vec3 delta_size)
{
    this->reset_model();
    this->m_size *= delta_size;
    this->m_model = glm::translate(this->m_model, this->m_position);

    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    this->m_model = glm::scale(this->m_model, this->m_size);
}

void Transform::SetSize(glm::vec3 size)
{
    this->reset_model();
    this->m_size = size;
    this->m_model = glm::translate(this->m_model, this->m_position);

    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_model = glm::rotate(this->m_model, glm::radians(this->m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    this->m_model = glm::scale(this->m_model, this->m_size);
}

void Transform::Render(Shader& shader)
{
    this->m_renderer.Render(shader, this->m_model);
}