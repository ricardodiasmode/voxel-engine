//
// Created by ricar on 2/22/2025.
//

#include "world/chunk/chunk.h"

Chunk::Chunk()
{
    buildVoxels();
    buildMesh();
}

std::vector<glm::uint8> Chunk::fillChunk() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            for (int k = 0; k < CHUNK_SIZE; k++) {
                voxels[i + CHUNK_SIZE * j + CHUNK_AREA * k] = 1;
            }
        }
    }
    return voxels;
}

void Chunk::buildVoxels() {
    voxels.clear();

    for (int i = 0; i < CHUNK_VOL; i++)
        voxels.push_back(0);

    fillChunk();
}

void Chunk::buildMesh()
{
    mesh = std::make_unique<ChunkMesh>(this,
        "shaders/chunkVertex.glsl",
        "shaders/chunkFragment.glsl");
}

void Chunk::draw(const glm::mat4& view,
    const glm::mat4& perspective)
{
    mesh->draw(view, perspective);
}
