#version 330 core
in vec3 FragColor; // Color from vertex shader
out vec4 FragColorOut;

void main() {
    FragColorOut = vec4(FragColor, 1.0); // Set pixel color
}
