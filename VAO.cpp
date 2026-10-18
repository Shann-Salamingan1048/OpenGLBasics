#include "VAO.hpp"

#include <print>

VAO::VAO(std::string_view name)
    :m_Name{name}
{
    glGenVertexArrays(1, &m_ID);
    bind();
}

void VAO::linkAttrib(VBO& vbo, GLuint index, GLsizei size, GLenum type, GLboolean normalized, GLsizei stride, void* offset)
{
    vbo.bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
    vbo.unbind();
}

VAO::~VAO()
{
    std::println("{} got destroyed by destructor.", m_Name);
    if (m_ID != 0)
    {
        glDeleteVertexArrays(1, &m_ID);
        m_ID = 0;
    }
}

void VAO::bind()
{
    glBindVertexArray(m_ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    std::println("{} got deleted.", m_Name);
    if (m_ID != 0)
    {
        glDeleteVertexArrays(1, &m_ID);
        m_ID = 0;
    }
}
