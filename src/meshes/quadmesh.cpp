#include "meshes/quadmesh.h"

// Quad vertex data (x, y, z, r, g, b)
const std::vector<float> quadVertices = {
    // Position         // Color
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom-left (Red)
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom-right (Green)
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // Top-right (Blue)
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f   // Top-left (Yellow)
};

// Quad index data (if using EBO)
const std::vector<unsigned int> quadIndices = {
    0, 1, 2,
    2, 3, 0
};

QuadMesh::QuadMesh()
    : BaseMesh("shaders/quadVertex.glsl", "shaders/quadFragment.glsl", quadVertices, quadIndices) {}
