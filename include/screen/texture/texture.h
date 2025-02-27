#pragma once

#include <glad/glad.h>
#include <iostream>
#include "stb/image/stb_image.h"
#include <string>

class Texture {

private:
    GLuint textureID;

    std::string textureName;

public:
    // Load texture using stb_image
    Texture(const char* filename,
        const char* inTextureName);

    void bind(class Shader shader);
};



