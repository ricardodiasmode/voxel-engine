#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D text;

uniform vec3 textColor;

void main() {
    float alpha = texture(text, TexCoords).r; // Sample red channel
    color = vec4(textColor, alpha); // Apply text color with glyph alpha
}