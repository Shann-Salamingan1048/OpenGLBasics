cmake_minimum_required(VERSION 4.3)
project(OpenGLBasics LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find installed Libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)



add_executable(OpenGLBasics
        main.cpp
        core/src/glad.c
        Shader.cpp)

# Tell compiler where headers are
target_include_directories(OpenGLBasics
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/core/include
)

target_link_libraries(OpenGLBasics
        PRIVATE
        glfw
        OpenGL::GL
)

add_custom_target(sync_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:OpenGLBasics>/glsl

        COMMENT "Syncing shader and texture assets..."
)
add_dependencies(OpenGLBasics sync_assets)