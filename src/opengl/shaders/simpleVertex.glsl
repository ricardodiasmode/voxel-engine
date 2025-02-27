#version 330 core
layout(location = 0) in vec3 aPos;   // Position attribute
layout(location = 1) in vec3 aColor; // Color attribute

uniform mat4 view;
uniform mat4 projection;

out vec3 FragColor;  // Pass color to fragment shader

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
    FragColor = vec3(aColor);            // Pass color to fragment shader
}
