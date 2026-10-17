#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float rotation;
void main()
{
    float x = cos(rotation);
    float y = sin(rotation);

    vec2 rotated = vec2(
    x * aPos.x - y * aPos.y,
    y * aPos.x + x * aPos.y
    );
    gl_Position = vec4(
    rotated,
    aPos.z,
    1.0
    );
    ourColor = aColor;
}