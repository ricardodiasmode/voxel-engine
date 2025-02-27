#include "meshes/basemesh.h"

#include <utils/debug.h>
#include <glm/gtc/type_ptr.hpp>

void BaseMesh::setVertexData(const VertexData& inVertexData) {
	static constexpr auto POSITION_ATTRIBUTE_INDEX = 0; // assuming we will always set location index to 0
	static constexpr auto COLOR_ATTRIBUTE_INDEX = 1; // assuming we will always set color index to 0

	if (inVertexData.indices.empty() ||
		inVertexData.vertices.empty()) {
		throw std::invalid_argument("BaseMesh::setVertexData called with empty vertices");
		return;
	}

	vertexData = inVertexData;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(glm::uint8), vertexData.vertices.data(), GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);

	// Color Attribute
	glVertexAttribPointer(COLOR_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(COLOR_ATTRIBUTE_INDEX);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexData.indices.size() * sizeof(GLuint), vertexData.indices.data(), GL_STATIC_DRAW);
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

	updateView(view);
	updateProj(perspective);

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
