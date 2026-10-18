
#pragma once

#include <glad/glad.h>
#include <string_view>
#include "VBO.hpp"

class VAO
{
public:
    explicit VAO(std::string_view name);
    ~VAO();

    void linkAttrib(VBO& vbo, GLuint index, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride, void* offset);
    void bind();
    void unbind();
    void Delete();

    [[nodiscard]] std::string_view getName() const noexcept
    {
        return m_Name;
    }
private:
    std::string_view m_Name;
    GLuint m_ID{};

};
