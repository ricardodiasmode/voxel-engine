#pragma once
#include <opengl/shaders/shader.h>

class BaseMesh
{
public:
	Shader shader;

	std::vector<float> vertexData;
	std::vector<float> meshColors;

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;

protected:
	void setVertexData(const std::vector<float> &inVertexData);

	BaseMesh(const char *vertexPath, const char *fragmentPath, const std::vector<float> &inVertexData,
			 const std::vector<unsigned int> &inIndexData);

public:
	~BaseMesh();

	void draw();
	void activate();

	void updateView(const glm::mat4& view);
	void updateProj(const glm::mat4& perspective);
};
