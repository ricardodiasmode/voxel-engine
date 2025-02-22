//
// Created by ricar on 2/22/2025.
//

#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <glm/ext/scalar_uint_sized.hpp>
#include <memory>
#include "meshes/chunkmesh.h"

class Chunk {
public:
    static constexpr auto CHUNK_SIZE = 32;
    static constexpr auto HORIZONTAL_CHUNK_SIZE = CHUNK_SIZE/32;
    static constexpr auto CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
    static constexpr auto CHUNK_VOL = CHUNK_SIZE * CHUNK_AREA;

private:
    std::unique_ptr<ChunkMesh> mesh;

public:
    std::vector<glm::uint8> voxels;

public:
    Chunk();

    std::vector<glm::uint8> fillChunk();

    void buildVoxels();
    void buildMesh();

    void draw(const glm::mat4& view,
        const glm::mat4& perspective);
};



#endif //CHUNK_H
