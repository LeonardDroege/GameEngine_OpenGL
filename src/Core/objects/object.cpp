#include "object.hpp"

Object::Object(glm::mat4* view_matrix, glm::mat4* projection_matrix) : m_transform(Transform(view_matrix, projection_matrix))
{
    this->m_ID = UUID();
}
Object::~Object()
{
    
}

void Object::Draw(Shader& shader)
{
    this->m_transform.Render(shader);
}

void Object::Translate(glm::vec3 delta_position)
{
    this->m_transform.Translate(delta_position);
}
void Object::Rotate(glm::vec3 delta_rotation)
{
    this->m_transform.Rotate(delta_rotation);
}
void Object::Scale(glm::vec3 delta_size)
{
    this->m_transform.Scale(delta_size);
}
void Object::SetSize(glm::vec3 size)
{  
    this->m_transform.SetSize(size);
}