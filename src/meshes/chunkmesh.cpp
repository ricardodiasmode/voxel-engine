#include <meshes/chunkmesh.h>
#include "world/chunk/chunk.h"
#include "utils/debug.h"

ChunkMesh::ChunkMesh(Chunk* inChunk, 
	const char* vertexPath, const char* fragmentPath) :	BaseMesh(vertexPath, 
		fragmentPath)
{
	chunk = std::shared_ptr<Chunk>(inChunk);

	setVertexData(getVertexData());
}

bool ChunkMesh::isVoid(const glm::vec3& voxelPos, const std::vector<glm::uint8>& voxels)
{
	glm::uint8 x = voxelPos.x;
	glm::uint8 y = voxelPos.y;
	glm::uint8 z = voxelPos.z;

	if (0 <= x && x < Chunk::CHUNK_SIZE &&
		0 <= y && y < Chunk::CHUNK_SIZE &&
		0 <= z && z < Chunk::CHUNK_SIZE)
	{
		return voxels[x + Chunk::CHUNK_SIZE * z + Chunk::CHUNK_AREA * y] == 0;
	}
	return true;
}

int ChunkMesh::addData(std::vector<glm::uint8>& inVertexData, 
	int byteOffset, 
	const std::vector<std::vector<int>>& vertices) {
	for (const auto& vertex : vertices) {
		for (int attr : vertex) {
			inVertexData.push_back(static_cast<glm::uint8>(attr));
		}
	}
	return byteOffset / VERTEX_ATTR_NUM + vertices.size();  // Return updated vertex count
}

VertexData ChunkMesh::getVertexData()
{
	assert(chunk.get());

	VertexData data;
	data.vertices.reserve(Chunk::CHUNK_VOL * 4 * VERTEX_ATTR_NUM);  // 4 vertices per face
	data.indices.reserve(Chunk::CHUNK_VOL * 6);  // 6 indices per face

	int index = 0;
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
	{
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
		{
			for (int k = 0; k < Chunk::CHUNK_SIZE; k++)
			{
				int voxelId = chunk->voxels[i + Chunk::CHUNK_SIZE * j + Chunk::CHUNK_AREA * k];
				if (voxelId == 0)
					continue;

				// checking top face
				if (isVoid(glm::vec3(i, j + 1, k), chunk->voxels))
				{ // make attribute for top face
					std::vector<int> v0 = { i, j + 1, k, voxelId, 0 };
					std::vector<int> v1 = { i + 1, j + 1, k, voxelId, 0 };
					std::vector<int> v2 = { i + 1, j + 1, k + 1, voxelId, 0 };
					std::vector<int> v3 = { i, j + 1, k + 1, voxelId, 0 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					); 
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}

				// checking bottom face
				if (isVoid(glm::vec3(i, j - 1, k), chunk->voxels))
				{ // make attribute for bottom face
					std::vector<int> v0 = { i, j, k, voxelId, 1 };
					std::vector<int> v1 = { i + 1, j, k, voxelId, 1 };
					std::vector<int> v2 = { i + 1, j, k + 1, voxelId, 1 };
					std::vector<int> v3 = { i, j, k + 1, voxelId, 1 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					);
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}

				// checking right face
				if (isVoid(glm::vec3(i + 1, j, k), chunk->voxels))
				{ // make attribute for right face
					std::vector<int> v0 = { i + 1, j, k, voxelId, 2 };
					std::vector<int> v1 = { i + 1, j + 1, k, voxelId, 2 };
					std::vector<int> v2 = { i + 1, j + 1, k + 1, voxelId, 2 };
					std::vector<int> v3 = { i + 1, j, k + 1, voxelId, 2 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					);
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}

				// checking left face
				if (isVoid(glm::vec3(i - 1, j, k), chunk->voxels))
				{ // make attribute for left face
					std::vector<int> v0 = { i, j, k, voxelId, 3 };
					std::vector<int> v1 = { i, j + 1, k, voxelId, 3 };
					std::vector<int> v2 = { i, j + 1, k + 1, voxelId, 3 };
					std::vector<int> v3 = { i, j, k + 1, voxelId, 3 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					);
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}

				// checking back face
				if (isVoid(glm::vec3(i, j, k - 1), chunk->voxels))
				{ // make attribute for back face
					std::vector<int> v0 = { i, j, k, voxelId, 4 };
					std::vector<int> v1 = { i, j + 1, k, voxelId, 4 };
					std::vector<int> v2 = { i + 1, j + 1, k, voxelId, 4 };
					std::vector<int> v3 = { i + 1, j, k, voxelId, 4 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					);
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}

				// checking front face
				if (isVoid(glm::vec3(i, j, k + 1), chunk->voxels))
				{ // make attribute for front face
					std::vector<int> v0 = { i, j, k + 1, voxelId, 5 };
					std::vector<int> v1 = { i, j + 1, k + 1, voxelId, 5 };
					std::vector<int> v2 = { i + 1, j + 1, k + 1, voxelId, 5 };
					std::vector<int> v3 = { i + 1, j, k + 1, voxelId, 5 };

					index = addData(data.vertices,
						index * VERTEX_ATTR_NUM,
						{ v0, v1, v2, v3 }
					);
					GLuint base = static_cast<GLuint>(index - 4);
					data.indices.insert(data.indices.end(), { base, base + 1, base + 2, base + 2, base + 3, base });
				}
			}
		}
	}

	size_t requiredSize = index * VERTEX_ATTR_NUM;
	if (requiredSize > data.vertices.max_size()) {
		throw std::length_error("Vertex data size exceeds vector max_size: " + std::to_string(requiredSize));
	}
	data.vertices.resize(index * VERTEX_ATTR_NUM);
	return data;
}
