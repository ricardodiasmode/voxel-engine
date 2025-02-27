//
// Created by ricar on 2/22/2025.
//

#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include <memory>
#include "meshes/basemesh.h"

class Chunk;

class ChunkMesh : public BaseMesh {
    static constexpr auto VERTEX_ATTR_NUM = 5;
    
private:
    std::shared_ptr<Chunk> chunk;

private:
    bool isVoid(const glm::vec3& voxelPos, const std::vector<glm::uint8>& voxels);

    int addData(std::vector<glm::uint8>& inVertexData,
        int byteOffset,
        const std::vector<std::vector<int>>& vertices);

protected:
    VertexData getVertexData();

    virtual void updateShader(const glm::mat4& view,
        const glm::mat4& perspective);

public:
    ChunkMesh(Chunk* inChunk,
        const char* vertexPath, const char* fragmentPath);

};

#endif //CHUNKMESH_H
