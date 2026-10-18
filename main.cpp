#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <print>
#include <chrono>

#include "Shader.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
class VAO;
class VBO;
class EBO;
int main()
{
    if (!glfwInit())
    {
        std::println(stderr, "Failed to initialize GLFW");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        800, 600, "OpenGL Basics", nullptr, nullptr
        );

    if (!window)
    {
        std::println(stderr, "Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // enable v-sync
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::println(stderr, "Failed to initialize GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0,0,width,height);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h)
    {
        glViewport(0,0,w,h);
    });

    {
        float vertices[] = {
            // Position
            -0.6f, -0.35f, 0.0f,
             0.6f, -0.35f, 0.0f,
             0.6f,  0.35f, 0.0f,
            -0.6f,  0.35f, 0.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        VAO vao{"Basta VAO"};
        VBO vbo{vertices, sizeof(vertices),"Basta VBO"};


        vao.bind();
        EBO ebo{indices, sizeof(indices),"Basta EBO"};
        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));

        vbo.unbind();
        vao.unbind();


        Shader shader("glsl/triangleRotate.vert","glsl/triangleRotate.frag", "Basta Shader");
        shader.use();
        shader.setVec3("ourColor", 0.0f,0.0f,1.0f);
        double lastSecond = glfwGetTime();

        float rotate = 0.0;
        constexpr uint8_t framePerSecond = 60;
        constexpr double timePerFrame = 1.0 / framePerSecond;
        while (!glfwWindowShouldClose(window))
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE)
                == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, true);
            }
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            double currentTime = glfwGetTime();

            if (currentTime - lastSecond >= timePerFrame)
            {
                rotate += glm::radians(10.0);

                lastSecond = currentTime;
            }


            shader.use();
            shader.setFloat("rotation", rotate);
            vao.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void *>(nullptr));

            glfwSwapBuffers(window);
            glfwPollEvents();

        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
