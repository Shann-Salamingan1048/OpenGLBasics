#pragma once

#include <glad/glad.h>
#include <string_view>
class VBO
{
public:
    explicit VBO(const GLfloat* vertices, GLsizeiptr size,std::string_view name);
    ~VBO();
    void Delete();
    void bind();
    void unbind();


    [[nodiscard]] std::string_view getName() const noexcept
    {
        return m_Name;
    }
private:
    std::string_view m_Name;
    GLuint m_ID{0};
};