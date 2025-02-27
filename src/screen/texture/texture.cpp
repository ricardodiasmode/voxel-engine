#include "screen/texture/texture.h"

Texture::Texture(const char* filename,
    const char* inTextureName)
{
    textureName = inTextureName;

    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determine image format
    GLenum format = (channels == 3) ? GL_RGB : GL_RGBA;

    // Upload texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Cleanup
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind
}

void Texture::bind(Shader shader)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(glGetUniformLocation(shader.ID, textureName.c_str()), 0);
}
