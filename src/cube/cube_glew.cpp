// Include standard headers
#include <iostream>
#include <vector>
#include <string>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Vertex shader source code
const char* vertex_shader_src = R"(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fragColor;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    fragColor = color;
}
)";

// Fragment shader source code
const char* fragment_shader_src = R"(
#version 330 core
in vec3 fragColor;

out vec4 color;

void main() {
    color = vec4(fragColor, 1.0);
}
)";

GLuint LoadShaders() {
    // Create the shaders
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Set the source code
    glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);

    // Compile the vertex shader
    glCompileShader(vertex_shader);
    GLint success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    // Compile the fragment shader
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    // Link the program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar info_log[512];
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    // Clean up shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Define the vertex data for a cube
    GLfloat vertices[] = {
        // Positions          // Colors
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    };

    GLuint indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 2, 6, 6, 5, 1,
        2, 3, 7, 7, 6, 2,
        3, 0, 4, 4, 7, 3,
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Load shaders and create shader program
    GLuint shader_program = LoadShaders();

    // Get the location of the uniform variables
    GLuint mvp_location = glGetUniformLocation(shader_program, "MVP");

    // Projection matrix
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    // View matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Check for events
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shader_program);

        // Update the Model matrix (rotate over time)
        Model = glm::rotate(Model, glm::radians(0.01f), glm::vec3(0.0f, 1.0f, 0.0f));
        MVP = Projection * View * Model;

        // Pass the new MVP matrix to the shader
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &MVP[0][0]);

        // Draw the cube
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    glfwTerminate();

    return 0;
}
