//
// Created by shann on 10/18/26.
//

#include "EBO.hpp"
#include <print>
EBO::EBO(const GLuint *indices,GLsizeiptr size, std::string_view name)
    : m_Name{name}
{

    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    std::println("{} got destroyed by destructor.", m_Name);
    if (m_ID != 0)
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::unbind()
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    std::println("{} got deleted.", m_Name);
    if (m_ID != 0)
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }

}
