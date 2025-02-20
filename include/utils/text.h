#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct GlyphChar {
    GLuint TextureID;  // Texture ID for glyph
    glm::ivec2 Size;   // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline
    GLuint Advance;    // Advance to next character
};

class Shader;

class Text
{
public:
    Text(const char* fontPath);

    std::map<char, GlyphChar> characters;

    GLuint VAO, VBO;

    void initTextRendering();

    void loadFont(const std::string& fontPath);

    void renderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
};
