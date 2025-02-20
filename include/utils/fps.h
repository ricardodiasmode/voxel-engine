#include <iostream>
#include <chrono>
#include "utils/debug.h"
#include "opengl/shaders/shader.h"

class Text;

namespace fps
{
    static std::unique_ptr<Shader> textShader = nullptr;

    float calculateFPS();

    void drawFPS(Text text);
}