#pragma once
#include <glad/glad.h>
#include <expected>
#include <string>
#include <glm/glm.hpp>
#include <system_error>
#include <filesystem>

class Shader
{
public:
    explicit Shader(const char* vertSource, const char* fragSource);
    // ~Shader(); deleteShaderProgram // optional lol
    [[nodiscard]] GLuint getID() const noexcept
    {
        return m_ID;
    }
    void use() const noexcept;
    void deleteShaderProgram() noexcept;
public:
    void setFloat(const std::string& name, float value) const;
    void setDouble(const std::string& name, double value) const;

    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
private:
    static std::expected<GLuint, std::string> createShaderProgram(const char* vertSource, const char* fragSource);
    static std::expected<GLuint, std::string> compileShader(GLenum type, const char* source);
    static std::expected<std::string, std::string> read_file_fast(const std::filesystem::path& path);
private:
    GLuint m_ID{0};
};
