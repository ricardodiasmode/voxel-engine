#version 330 core

layout(location = 0) in ivec3 aPos;
layout(location = 1) in int aVoxelId;
layout(location = 2) in int aFaceId;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 voxel_color;

vec3 hash31(float p) {
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
    voxel_color = hash31(aVoxelId);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
