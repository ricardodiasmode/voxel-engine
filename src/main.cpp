#include <component-owner/player/player.h>
#include <glad/glad.h>
#include <meshes/quadmesh.h>

#include "utils/text.h"
#include "utils/fps.h"
#include <window/window.h>

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

    QuadMesh quadMesh;

    std::unique_ptr<Player> player = std::make_unique<Player>(window->getWindow());

    // Render Loop
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fps::drawFPS(fpsText);

        player->update();

        quadMesh.activate();
        quadMesh.updateView(player->getView());
        quadMesh.updateProj(player->getProj());
        quadMesh.draw();

        // Swap buffers and poll events
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
