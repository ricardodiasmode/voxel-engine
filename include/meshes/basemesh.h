#pragma once
#include <opengl/shaders/shader.h>

struct VertexData {
	std::vector<glm::uint8> vertices;
	std::vector<GLuint> indices;

	void printVertices() {
		std::cout << "[";
		std::copy(vertices.begin(), vertices.end(), std::ostream_iterator<int>(std::cout, ", "));
		std::cout << "\b\b]" << std::endl; // Backspace to remove trailing ", "
	}
};

class BaseMesh
{
protected:
	std::string shaderName = std::string("BaseMeshShader");

public:
	Shader shader;

	VertexData vertexData;
	std::vector<float> meshColors;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

private:
	void activate();
	void updateView(const glm::mat4& view);
	void updateProj(const glm::mat4& perspective);

protected:
	virtual void setVertexData(const VertexData& inVertexData);

	virtual void updateShader(const glm::mat4& view,
		const glm::mat4& perspective);

	BaseMesh(const char *vertexPath, 
		const char *fragmentPath);

public:
	~BaseMesh();

	void draw(const glm::mat4& view,
		const glm::mat4& perspective);

	int getAttrNum() { return 5; }
};
