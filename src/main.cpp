#include <glad/glad.h>
#include "utils/glhandler.h"
#include "utils/text.h"
#include "utils/fps.h"

int main()
{
    if (!glHandler::initialize())
        return -1;

    // Load font and set up text rendering
    Text fpsText = Text("resources/fonts/arial/ARIAL.ttf");  // Change to a real font path

    // Render Loop
    while (!glfwWindowShouldClose(glHandler::window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        fps::drawFPS(fpsText);

        // Swap buffers and poll events
        glfwSwapBuffers(glHandler::window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
