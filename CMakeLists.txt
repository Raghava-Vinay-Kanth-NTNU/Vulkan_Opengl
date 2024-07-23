cmake_minimum_required(VERSION 3.10)
project(OpenGLCube)
# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
    "E:/C++/Vulkan_Opengl/include"
    "E:/C++/Vulkan_Opengl/include/Vulkan/Include"
)

# Link directories
link_directories(
    "E:/C++/Vulkan_Opengl/lib"
)

add_executable(OpenGLCube
    ${CMAKE_SOURCE_DIR}/src/cube/cube_glew.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/vulkan/engine.cpp
)

target_link_libraries(OpenGLCube
    glew32
    glfw3
    opengl32
    gdi32
)

# Add any necessary definitions
add_definitions(-DGLEW_STATIC)
