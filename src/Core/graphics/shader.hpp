#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../global.hpp"

class Shader
{
    public:
        Shader(const std::string& vertex_code, const std::string& fragment_code);
        ~Shader();

        void Use();
        void Destroy();

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, glm::vec2& value) const;
        void SetVec3(const std::string& name, glm::vec3& value) const;
        void SetVec4(const std::string& name, glm::vec4& value) const;
        void SetMat2(const std::string& name, glm::mat2& value) const;
        void SetMat3(const std::string& name, glm::mat3& value) const;
        void SetMat4(const std::string& name, glm::mat4& value) const;
        void SetColor(const std::string& name, Color& value) const;

    private:
        unsigned int m_id;

        std::string m_vertex_code;
        std::string m_fragment_code;

        void load_shader(const char* path, std::string* out);
        void init();
        void check_compile_error(unsigned int shader, const std::string type);
        void check_linking_error();

};

#endif