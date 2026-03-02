#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "../uuid.hpp"
#include "../graphics/shader.hpp"
#include "../global.hpp"

class Renderer
{
    public:
        Renderer(glm::mat4* view_matrix, glm::mat4* projection_matrix, const std::vector<float> vertices = {
                    0.0f, 1.0f, 0.0f, //V
                    1.0f, 0.0f, 0.0f, //C
                    -1.0f, -0.5f, 0.0f, //V
                    0.0f, 1.0f, 0.0f, //C
                    1.0f, -0.5f, 0.0f, //V
                    0.0f, 0.0f, 1.0f //C
                },
                const std::vector<unsigned int> indices = {
                    0, 1, 2
                });
        Renderer(glm::mat4* view_matrix, glm::mat4* projection_matrix, Color color, const std::vector<float> vertices = {
                0.0f, 1.0f, 0.0f, //V
                1.0f, 0.0f, 0.0f, //C
                -1.0f, -0.5f, 0.0f, //V
                0.0f, 1.0f, 0.0f, //C
                1.0f, -0.5f, 0.0f, //V
                0.0f, 0.0f, 1.0f //C
            },
            const std::vector<unsigned int> indices = {
                0, 1, 2
            });
        ~Renderer();

        void Render(Shader& shader, glm::mat4& model);

        void SetData(const std::vector<float> vertices, const std::vector<unsigned int> indices, bool unbind = true);
        void SetData(const std::vector<float> vertices, bool unbind = true);
        void SetData(const std::vector<unsigned int> indices, bool unbind = true);

    private:
        void initialize_components(const std::vector<float> vertices, const std::vector<unsigned int> indices);

    private:
        UUID m_ID;

        unsigned int m_vao;
        unsigned int m_vbo;
        unsigned int m_ebo;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        glm::mat4* m_view_matrix_ptr;
        glm::mat4* m_projection_matrix_ptr;

        Color m_color;
};

#endif