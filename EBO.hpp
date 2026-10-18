#pragma once
#include <string_view>
#include <glad/glad.h>



class EBO
{
public:
    explicit EBO(const GLuint* indices,GLsizeiptr size, std::string_view name);
    ~EBO();


    void bind();
    void unbind();
    void Delete();


    [[nodiscard]] std::string_view getName() const noexcept
    {
        return m_Name;
    }


private:
    std::string_view m_Name;
    GLuint m_ID{0};
};