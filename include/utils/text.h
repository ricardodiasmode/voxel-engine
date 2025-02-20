#include <iostream>
#include <map>
#include <string>

// OpenGL and GLM headers
#include <glad/glad.h>  // Ensure GLAD is initialized
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl/shaders/shader.h"

// FreeType headers
#include <ft2build.h>
#include FT_FREETYPE_H

namespace text
{
    struct GlyphChar {
        GLuint TextureID;  // Texture ID for glyph
        glm::ivec2 Size;   // Size of glyph
        glm::ivec2 Bearing; // Offset from baseline
        GLuint Advance;    // Advance to next character
    };
    std::map<char, GlyphChar> Characters;

    GLuint VAO, VBO;
    void initTextRendering() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glEnable(GL_BLEND); // Ensure blending is on
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void loadFont(const std::string& fontPath) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERROR: FreeType could not be initialized." << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            std::cerr << "ERROR: Failed to load font at " << fontPath << std::endl;
            FT_Done_FreeType(ft);
            return;
        }

        if (FT_Set_Pixel_Sizes(face, 0, 48)) {
            std::cerr << "ERROR: Failed to set font size to 48 pixels" << std::endl;
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            return;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        int loadedGlyphs = 0;
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "ERROR: Failed to load glyph '" << c << "'" << std::endl;
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            GlyphChar character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
            };
            Characters[c] = character;
            loadedGlyphs++;
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        std::cout << "Font loaded successfully. Loaded " << loadedGlyphs << " glyphs." << std::endl;
    }

    void renderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color) {
        shader.use();
        shader.setVec3("textColor", color);
        shader.setInt("text", 0); // Ensure texture unit is set
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for (char c : text) {
            if (Characters.find(c) == Characters.end()) {
                std::cerr << "Glyph not found for " << c << std::endl;
                continue;
            }
            GlyphChar ch = Characters[c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR) {
                std::cerr << "OpenGL error after drawing '" << c << "': " << err << std::endl;
            }

            x += (ch.Advance >> 6) * scale;
        }
        glBindVertexArray(0);
    }
}
