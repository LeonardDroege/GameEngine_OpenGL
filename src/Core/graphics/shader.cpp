#include "shader.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
    load_shader(vertex_path.c_str(), &this->m_vertex_code);
    load_shader(fragment_path.c_str(), &this->m_fragment_code);
    this->init();
}
Shader::~Shader()
{
    this->Destroy();
}

void Shader::Use()
{
    glUseProgram(this->m_id);
}
void Shader::Destroy()
{
    glDeleteProgram(this->m_id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), value);
}
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(this->m_id, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(this->m_id, name.c_str()), value);
}
void Shader::SetVec2(const std::string& name, glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::SetVec3(const std::string& name, glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::SetVec4(const std::string& name, glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::SetMat2(const std::string& name, glm::mat2& value) const
{
    glUniformMatrix2fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetMat3(const std::string& name, glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetMat4(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetColor(const std::string& name, Color& value) const
{
    float rValue = value.r > 0 ? (float)(value.r) / 255.0f : 0.0f;
    float gValue = value.g > 0 ? (float)(value.g) / 255.0f : 0.0f;
    float bValue = value.b > 0 ? (float)(value.b) / 255.0f : 0.0f;
    float aValue = value.a > 0 ? (float)(value.a) / 255.0f : 0.0f;
    glUniform4f(glGetUniformLocation(this->m_id, "u_color"), rValue, gValue, bValue, aValue);
}

void Shader::load_shader(const char* path, std::string* out)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream fileStream;
    try
    {
        file.open(path);
        fileStream << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Shader: error reading shader file: " << path << std::endl;
    }

    *out = fileStream.str();
}

void Shader::init()
{
    const char* vertex_code = this->m_vertex_code.c_str();
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_code, NULL);
    glCompileShader(vertex_shader);
    check_compile_error(vertex_shader, "Vertex Shader");

    const char* fragment_code = this->m_fragment_code.c_str();
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_code, NULL);
    glCompileShader(fragment_shader);
    check_compile_error(fragment_shader, "Fragment Shader");

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);
    check_linking_error();
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::check_compile_error(unsigned int shader, const std::string type)
{
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "Shader: Error compiling " << type << ":" << std::endl
                  << infoLog
                  << std::endl;
    }
}

void Shader::check_linking_error()
{
    int success;
    char infoLog[1024];
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 1024, NULL, infoLog);
        std::cout << "Shader: Error linking shader program: " << std::endl
                  << infoLog
                  << std::endl;
    }
}