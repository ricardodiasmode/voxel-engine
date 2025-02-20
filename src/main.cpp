#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "utils/glhandler.h"
#include "utils/text.h"
#include "utils/fps.h"
#include "opengl/shaders/shader.h"

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

    // Create shader program from files
    unsigned int shaderProgram = glHandler::createShaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    Shader textShader("shaders/textVertex.glsl", "shaders/textFragment.glsl", "TextShader"); // Load your shaders
    textShader.use();
    textShader.setInt("text", 0); // Texture unit 0
    glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.0f, 600.f);
    textShader.setMat4("projection", projection);

    // Load font and set up text rendering
    text::loadFont("resources/fonts/arial/ARIAL.ttf");  // Change to a real font path
    text::initTextRendering();

    glEnable(GL_BLEND); // Ensure blending is on
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render Loop
    while (!glfwWindowShouldClose(glHandler::window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use Shader Program
        glUseProgram(shaderProgram);

        // Bind VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        float fps = calculateFPS();
        std::string fpsText = "FPS: " + std::to_string((int)fps);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        text::renderText(textShader, fpsText, 10.0f, 560.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);

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
