#include "utils/fps.h"
#include "opengl/shaders/shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "utils/text.h"

float fps::calculateFPS() {
    static auto lastTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float elapsedTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastTime).count();

    lastTime = currentTime; // Update lastTime for the next frame

    if (elapsedTime < 0.001f) { // Prevent division by near-zero (e.g., < 1 microsecond)
        elapsedTime = 0.001f;   // Cap at 1000 FPS
    }

    return 1000.f / elapsedTime; // FPS = 1000 ms / frame time in ms
}

void fps::drawFPS(Text text)
{
    if (!textShader)
    {
        textShader = std::make_unique<Shader>("shaders/textVertex.glsl", "shaders/textFragment.glsl", "TextShader"); // Load your shaders
        textShader->use();
        textShader->setInt("text", 0); // Texture unit 0
        glm::mat4 projection = glm::ortho(0.0f, 800.f, 0.0f, 600.f);
        textShader->setMat4("projection", projection);
    }

    float fps = calculateFPS();
    std::string fpsText = "FPS: " + std::to_string((int)fps);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    text.renderText(*textShader, fpsText, 10.0f, 560.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
}
