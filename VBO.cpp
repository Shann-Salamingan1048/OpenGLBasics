#include "VBO.hpp"
#include <print>
VBO::VBO(const GLfloat *vertices, GLsizeiptr size,std::string_view name)
    :m_Name{name}
{
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    std::println("{} got destroyed by destructor.", m_Name);
    glDeleteBuffers(1, &m_ID);
}

void VBO::Delete()
{
    std::println("{} got deleted.", m_Name);
    if (m_ID != 0)
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
