#include <component-owner/player/player.h>
#include <glad/glad.h>
#include <meshes/chunkmesh.h>

#include "utils/text.h"
#include "utils/fps.h"
#include <window/window.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    std::unique_ptr<Window> window = std::make_unique<Window>();
    if (!window.get())
    {
        std::cout << "Failed to initialize window" << std::endl;
        return -1;
    }

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    window->initializeGL();

    // Load font and set up text rendering
    Text fpsText = Text("resources/fonts/arial/ARIAL.ttf");  // Change to a real font path

    /*std::unique_ptr<ChunkMesh> chunk = std::make_unique<ChunkMesh>("shaders/simpleVertex.glsl",
        "shaders/simpleFragment.glsl");*/

    std::unique_ptr<Player> player = std::make_unique<Player>(window->getWindow());

    GLuint VAO, VBO;
    float cubeVertices[] = {
        // Position            // Color
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  // Red
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  // Green
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,  // Blue
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  // Yellow
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,  // Magenta
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,  // Cyan
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // White
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f   // Black
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 16 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader = Shader("shaders/simpleVertex.glsl",
        "shaders/simpleFragment.glsl", "test");

    // Render Loop
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fps::drawFPS(fpsText);

        player->update();

        glUseProgram(shader.ID);  // Use a valid shader program

        GLint location = glGetUniformLocation(shader.ID, "view");

        // Check if the location is valid (not -1)
        if (location == -1) {
            std::cerr << "Warning: uniform " << "view" << " not found in the shader!" << std::endl;
        }

        // Set the matrix uniform in the shader
        print(glm::to_string(player->getView()));
        glUniformMatrix4fv(location, 1, GL_FALSE, &player->getView()[0][0]);

        location = glGetUniformLocation(shader.ID, "projection");

        // Check if the location is valid (not -1)
        if (location == -1) {
            std::cerr << "Warning: uniform " << "projection" << " not found in the shader!" << std::endl;
        }

        // Set the matrix uniform in the shader
        glUniformMatrix4fv(location, 1, GL_FALSE, &player->getProj()[0][0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        //chunk->draw(player->getView(), player->getProj());

        // Swap buffers and poll events
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
