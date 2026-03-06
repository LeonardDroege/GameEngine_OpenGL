#include "object.hpp"

Object::Object(glm::mat4* view_matrix, glm::mat4* projection_matrix) : m_renderer(Renderer(view_matrix, projection_matrix, Color {255, 200, 100, 50}))
{
    this->m_ID = UUID();
    this->m_model = glm::mat4(1.0);
    this->m_transform = Transform();
}
Object::~Object()
{
    
}

void Object::Draw(Shader& shader)
{
    this->m_renderer.Render(shader, this->m_model);
}

void Object::Translate(glm::vec3 delta_position)
{
    this->m_model = glm::mat4(1.0);
    this->m_transform.Translate(delta_position, &this->m_model);
}
void Object::Rotate(glm::vec3 delta_rotation)
{
    this->m_model = glm::mat4(1.0);
    this->m_transform.Rotate(delta_rotation, &this->m_model);
}
void Object::Scale(glm::vec3 delta_size)
{
    this->m_model = glm::mat4(1.0);
    this->m_transform.Scale(delta_size, &this->m_model);
}
void Object::SetSize(glm::vec3 size)
{  
    this->m_model = glm::mat4(1.0);
    this->m_transform.SetSize(size, &this->m_model);
}