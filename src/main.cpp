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

    // Load font and set up text rendering
    text::loadFont("resources/fonts/arial/ARIAL.ttf");  // Change to a real font path
    text::initTextRendering();

    // Render Loop
    while (!glfwWindowShouldClose(glHandler::window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fps::drawFPS();

        // Swap buffers and poll events
        glfwSwapBuffers(glHandler::window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
