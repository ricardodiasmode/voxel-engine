#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "utils/glhandler.h"

int main()
{

    if (!glHandler::initialize())
        return -1;

    // Define the triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
         0.5f, -0.5f, 0.0f, // Right
         0.0f,  0.5f, 0.0f  // Top
    };

    // Create VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO first
    glBindVertexArray(VAO);

    // Bind the VBO and copy data into it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    // Create shader program from files
    unsigned int shaderProgram = glHandler::createShaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    // Render Loop
    while (!glfwWindowShouldClose(glHandler::window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use Shader Program
        glUseProgram(shaderProgram);

        // Bind VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll events
        glfwSwapBuffers(glHandler::window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
