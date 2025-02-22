//
// Created by ricar on 2/21/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {

public:
    static constexpr float WIDTH = 1600.f;
    static constexpr float HEIGHT = 900.f;

  private:
    GLFWwindow* window = nullptr;

    std::string title = "Voxel Engine";

public:
    Window();

    void initializeGL();

    inline GLFWwindow* getWindow() const { return window; }
};



#endif //WINDOW_H
