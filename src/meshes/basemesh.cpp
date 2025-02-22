#include "meshes/basemesh.h"

#include <utils/debug.h>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void BaseMesh::setVertexData(const std::vector<float> &inVertexData) {
	static constexpr auto POSITION_ATTRIBUTE_INDEX = 0; // assuming we will always set location index to 0
	static constexpr auto COLOR_ATTRIBUTE_INDEX = 1; // assuming we will always set color index to 0

	if (inVertexData.empty()) {
		printError("BaseMesh::setVertexData called with empty vertices");
		return;
	}

	vertexData = inVertexData;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);

	// Color Attribute
	glVertexAttribPointer(COLOR_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(COLOR_ATTRIBUTE_INDEX);
}

BaseMesh::BaseMesh(const char* vertexPath, const char* fragmentPath,
				   const std::vector<float>& inVertexData,
				   const std::vector<unsigned int>& inIndexData)
	: shader(Shader(vertexPath, fragmentPath, "BaseMeshShader")) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);  // Generate EBO

	glBindVertexArray(VAO);

	setVertexData(inVertexData);

	// Bind EBO and set index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inIndexData.size() * sizeof(unsigned int), inIndexData.data(), GL_STATIC_DRAW);
}

BaseMesh::~BaseMesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void BaseMesh::draw() {
	glBindVertexArray(VAO);  // Bind the VAO (contains VBO & EBO)

	if (EBO) {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // Draw using indices
	} else {
		glDrawArrays(GL_TRIANGLES, 6, 0);  // Alternative if using VBO only
	}

	glBindVertexArray(0);  // Unbind for safety
}

void BaseMesh::activate() {
	shader.use();  // Activate the shader
}

void BaseMesh::updateView(const glm::mat4& view) {
	shader.setMat4("view", view);
}

void BaseMesh::updateProj(const glm::mat4 &perspective) {
	shader.setMat4("projection", perspective);
}

