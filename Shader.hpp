#pragma once
#include <glad/glad.h>
#include <expected>
#include <string>
#include <glm/glm.hpp>
#include <system_error>
#include <filesystem>
#include <string_view>
class Shader
{
public:
    explicit Shader(const char* vertSource, const char* fragSource, std::string_view name);
    ~Shader();
    [[nodiscard]] GLuint getID() const noexcept
    {
        return m_ID;
    }
    void use() const noexcept;
    void deleteShaderProgram() noexcept;
public:
    void setFloat(std::string_view name, float value) const;
    void setDouble(std::string_view name, double value) const;

    void setVec2(std::string_view name, const glm::vec2& value) const;
    void setVec2(std::string_view name, float x, float y) const;

    void setVec3(std::string_view name, const glm::vec3& value) const;
    void setVec3(std::string_view name, float x, float y, float z) const;
public:
    [[nodiscard]] std::string_view getName() const noexcept
    {
        return m_Name;
    }
private:
    static std::expected<GLuint, std::string_view> createShaderProgram(const char* vertSource, const char* fragSource);
    static std::expected<GLuint, std::string_view> compileShader(GLenum type, const char* source);
    static std::expected<std::string, std::string_view> read_file_fast(const std::filesystem::path& path);

private:
    std::string m_Name;
    GLuint m_ID{0};
};
