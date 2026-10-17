//
// Created by shann on 10/15/26.
//
#include "Shader.hpp"

#include <print>
#include <fstream>

std::expected<GLuint, std::string> Shader::createShaderProgram(const char* vertSource, const char* fragSource)
{
    auto vertAlreadyRead = read_file_fast(vertSource);
    if (!vertAlreadyRead)
    {
        return std::unexpected(vertAlreadyRead.error());
    }
    auto vertShaderResult = compileShader(GL_VERTEX_SHADER, vertAlreadyRead->data());
    if (!vertShaderResult)
    {
        return std::unexpected("Vertex Shader Error: " + vertShaderResult.error());
    }

    auto fragAlreadyRead = read_file_fast(fragSource);
    if (!fragAlreadyRead)
    {
        return std::unexpected(fragAlreadyRead.error());
    }
    auto fragShaderResult = compileShader(GL_FRAGMENT_SHADER, fragAlreadyRead->data());
    if (!fragShaderResult)
    {
        glDeleteShader(*vertShaderResult);
        return std::unexpected("Fragment Shader Error: " + fragShaderResult.error());
    }

    auto program = glCreateProgram();
    glAttachShader(program,*vertShaderResult);
    glAttachShader(program,*fragShaderResult);
    glLinkProgram(program);

    glDeleteShader(*vertShaderResult);
    glDeleteShader(*fragShaderResult);

    int success{0};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');
        glGetShaderInfoLog(program, 512, nullptr, infoLog.data());
        glDeleteShader(program);
        return std::unexpected("Shader Link Error: " + infoLog);
    }
    return program;
}

std::expected<GLuint, std::string> Shader::compileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success{0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string infoLog(512, '\0');
        glGetShaderInfoLog(shader, 512, nullptr, infoLog.data());
        glDeleteShader(shader);
        return std::unexpected(infoLog);
    }

    return shader;
}

Shader::Shader(const char *vertSource, const char *fragSource)
{
    auto shaderResult = createShaderProgram(vertSource, fragSource);
    if (!shaderResult)
    {
        std::println(stderr,"{}",shaderResult.error());
        return;
    }
    m_ID = *shaderResult;
}

std::expected<std::string, std::string> Shader::read_file_fast(const std::filesystem::path &path)
{
    /// Open in binary mode and seek to the end (ate) to immediately get file size
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory).message());
    }

    const auto size = file.tellg();
    if (size < 0) {
        return std::unexpected(std::make_error_code(std::errc::io_error).message());
    }

    file.seekg(0, std::ios::beg);

    std::string content;
    // C++23: Allocates buffer without redundant zero-initialization
    content.resize_and_overwrite(static_cast<std::size_t>(size), [&](char* buf, std::size_t n) {
        file.read(buf, static_cast<std::streamsize>(n));
        return static_cast<std::size_t>(file.gcount());
    });

    if (file.bad()) {
        return std::unexpected(std::make_error_code(std::errc::io_error).message());
    }

    return content;
}


void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ID, name.data()), value);
}
void Shader::setDouble(const std::string &name, double value) const
{
    glUniform1d(glGetUniformLocation(m_ID, name.data()), value);
}


void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_ID, name.data()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_ID, name.data()), x,y);
}

void Shader::deleteShaderProgram() noexcept
{
    if (m_ID != 0)
    {
        glDeleteProgram(m_ID);
        m_ID = 0;
    }
}

void Shader::use() const noexcept
{
    glUseProgram(m_ID);
}
