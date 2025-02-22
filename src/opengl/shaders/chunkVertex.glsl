#version 330 core

layout(location = 0) in ivec3 aPos;
layout(location = 1) in int aVoxelId;
layout(location = 2) in int aFaceId;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
