#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

namespace glHandler
{
    static GLFWwindow* window = nullptr;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool initialize()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            std::cout << "Failed to initialize GLFW." << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

        // Create Window
        window = glfwCreateWindow(800, 600, "Voxel Engine", NULL, NULL);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);

        // Load OpenGL function pointers using GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Enabling depth test
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Enable VSync to cap FPS
        glfwSwapInterval(0); 

        return true;
    }

    // Function to read shader source code from file
    std::string readShaderFile(const char* filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "ERROR: Could not open shader file: " << filePath << std::endl;
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf(); // Read file content into stream
        return buffer.str();
    }

    // Function to compile shader
    unsigned int compileShader(unsigned int type, const std::string& source)
    {
        unsigned int shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // Check for errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
        }

        return shader;
    }

    // Function to create shader program
    unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath)
    {
        // Read shader sources from files
        std::string vertexCode = readShaderFile(vertexPath);
        std::string fragmentCode = readShaderFile(fragmentPath);

        // Compile shaders
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

        // Link shaders into a program
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
        }

        // Delete shaders after linking
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }
}