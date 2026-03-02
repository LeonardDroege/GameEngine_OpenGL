#include "renderer.hpp"
#include <glad/glad.h>

Renderer::Renderer(glm::mat4* view_matrix, glm::mat4* projection_matrix, const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    this->m_ID = UUID();
    this->m_view_matrix_ptr = view_matrix;
    this->m_projection_matrix_ptr = projection_matrix;
    this->m_color = {255, 255, 255, 255};
    this->initialize_components(vertices, indices);
}
Renderer::Renderer(glm::mat4* view_matrix, glm::mat4* projection_matrix, Color color, const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    this->m_ID = UUID();
    this->m_view_matrix_ptr = view_matrix;
    this->m_projection_matrix_ptr = projection_matrix;
    this->m_color = color;
    this->initialize_components(vertices, indices);
}
Renderer::~Renderer()
{
    glDeleteBuffers(1, &this->m_ebo);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteVertexArrays(1, &this->m_vao);
}

void Renderer::Render(Shader& shader, glm::mat4& model)
{
    shader.SetColor("u_color", this->m_color);
    shader.SetMat4("u_model", model);
    shader.SetMat4("u_view", *this->m_view_matrix_ptr);
    shader.SetMat4("u_projection", *this->m_projection_matrix_ptr);

    glBindVertexArray(this->m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);

    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::SetData(const std::vector<float> vertices, const std::vector<unsigned int> indices, bool unbind)
{
    this->m_vertices = vertices;
    this->m_indices = indices;

    glBindVertexArray(this->m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(float), this->m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(unsigned int), this->m_indices.data(), GL_STATIC_DRAW);

    if(!unbind) return;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::SetData(const std::vector<float> vertices, bool unbind)
{
    this->m_vertices = vertices;

    glBindVertexArray(this->m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(float), this->m_vertices.data(), GL_STATIC_DRAW);

    if(!unbind) return;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::SetData(const std::vector<unsigned int> indices, bool unbind)
{
    this->m_indices = indices;

    glBindVertexArray(this->m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(unsigned int), this->m_indices.data(), GL_STATIC_DRAW);

    if(!unbind) return;

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::initialize_components(const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    glGenVertexArrays(1, &this->m_vao);
    glGenBuffers(1, &this->m_vbo);
    glGenBuffers(1, &this->m_ebo);

    this->SetData(vertices, indices, false);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}