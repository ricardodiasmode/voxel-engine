#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TextureCoord;
in vec3 voxel_color;
in vec2 UV;

uniform sampler2D Texture;

void main()
{
    vec3 TextureColor = texture(Texture, UV).rgb;
    FragColor = vec4(TextureColor, 1);
}