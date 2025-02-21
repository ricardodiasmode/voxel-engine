#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int ID;
    
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* shaderName);

    ~Shader();

    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) {
        GLint location = glGetUniformLocation(ID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void setMat4(const std::string& name, const glm::mat4& value) const {
        // Get the location of the uniform in the shader program
        GLint location = glGetUniformLocation(ID, name.c_str());

        // Check if the location is valid (not -1)
        if (location == -1) {
            std::cerr << "Warning: uniform " << name << " not found in the shader!" << std::endl;
        }

        // Set the matrix uniform in the shader
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }


private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif