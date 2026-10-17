#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <print>
#include <chrono>
#include <thread>
#include "Shader.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

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


    float vertices[] = {
        // Position          // Color
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("glsl/triangleRotate.vert","glsl/triangleRotate.frag");

    double lastSecond = glfwGetTime();

    float rotate = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        double frameStart = glfwGetTime();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE)
            == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();

        if (currentTime - lastSecond >= 1.0)
        {

            rotate += glm::radians(10.0);

            lastSecond = currentTime;
        }


        shader.setFloat("rotation", rotate);
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.deleteShaderProgram();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
