#include "meshes/basemesh.h"

#include <utils/debug.h>
#include <glm/gtc/type_ptr.hpp>

void BaseMesh::setVertexData(const VertexData& inVertexData) {
	static constexpr auto POSITION_ATTRIBUTE_INDEX = 0;
	static constexpr auto VOXEL_ID_ATTRIBUTE_INDEX = 1;
	static constexpr auto FACE_ID_ATTRIBUTE_INDEX = 2;

	if (inVertexData.indices.empty() || inVertexData.vertices.empty()) {
		throw std::invalid_argument("BaseMesh::setVertexData called with empty vertices");
	}

	vertexData = inVertexData;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(glm::uint8), vertexData.vertices.data(), GL_STATIC_DRAW);

	// Assuming 5 attributes per vertex: x, y, z, voxelId, faceId (each 1 byte)
	const int stride = 5 * sizeof(glm::uint8);

	// Position Attribute (ivec3)
	glVertexAttribIPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_UNSIGNED_BYTE, stride, (void*)0);
	glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);

	// Voxel ID Attribute (int)
	glVertexAttribIPointer(VOXEL_ID_ATTRIBUTE_INDEX, 1, GL_UNSIGNED_BYTE, stride, (void*)(3 * sizeof(glm::uint8)));
	glEnableVertexAttribArray(VOXEL_ID_ATTRIBUTE_INDEX);

	// Face ID Attribute (int)
	glVertexAttribIPointer(FACE_ID_ATTRIBUTE_INDEX, 1, GL_UNSIGNED_BYTE, stride, (void*)(4 * sizeof(glm::uint8)));
	glEnableVertexAttribArray(FACE_ID_ATTRIBUTE_INDEX);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexData.indices.size() * sizeof(GLuint), vertexData.indices.data(), GL_STATIC_DRAW);
}

void BaseMesh::updateShader(const glm::mat4& view,
	const glm::mat4& perspective)
{
	updateView(view);
	updateProj(perspective);
}

BaseMesh::BaseMesh(const char* vertexPath, 
	const char* fragmentPath)
	: VBO(0),
	shader(Shader(vertexPath, fragmentPath, shaderName.c_str())) {

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO); 
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

BaseMesh::~BaseMesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void BaseMesh::draw(const glm::mat4& view,
	const glm::mat4& perspective) {

	GLenum err = glGetError();
	if (err == GL_OUT_OF_MEMORY) {
		print("GL_OUT_OF_MEMORY before draw mesh");
	}

	activate();

	updateShader(view, perspective);

	glBindVertexArray(VAO);  // Bind the VAO (contains VBO & EBO)

	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL error before draw: " << err << std::endl;
	}

	glDrawElements(GL_TRIANGLES, vertexData.indices.size(), GL_UNSIGNED_INT, 0);  // Draw using indices

	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "OpenGL error after draw: " << err << std::endl;
	}

	glBindVertexArray(0);  // Unbind for safety

	err = glGetError();
	if (err == GL_OUT_OF_MEMORY) {
		print("GL_OUT_OF_MEMORY after draw mesh");
	}
}

void BaseMesh::activate() {
	assert(!vertexData.vertices.empty()); // must not activate a empty mesh

	shader.use();  // Activate the shader
}

void BaseMesh::updateView(const glm::mat4& view) {
	shader.setMat4("view", view);
}

void BaseMesh::updateProj(const glm::mat4 &perspective) {
	shader.setMat4("projection", perspective);
}
