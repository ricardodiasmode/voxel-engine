#version 330 core

layout(location = 0) in ivec3 aPos;
layout(location = 1) in int aVoxelId;
layout(location = 2) in int aFaceId;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 voxel_color;
out vec2 UV;

const vec2 UVCoords[4] = vec2[4](
    vec2(0, 0), vec2(0, 1),
    vec2(1, 0), vec2(1, 1)
    );

const int UVIndices[12] = int[12](
    1, 0, 2, 1, 2, 3 // coords for even faces
    3, 0, 2, 3, 1, 0 // coords for odd faces
    );

vec3 hash31(float p) {
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
    int UVIndex = gl_VertexID % 6 + (aFaceId & 1) * 6;
    UV = UVCoords[UVIndices[UVIndex]];
    voxel_color = hash31(aVoxelId);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
