#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Component {
protected:
	glm::vec3 position;
	float pitch;
	float yaw;

	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 forwardVector;

public:
	Component(const glm::vec3 inPos,
		const int inPitch,
		const int inYaw);

	virtual void rotateUp(const float delta);
	virtual void rotateRight(const float delta);
	virtual void rotate(const glm::vec2 delta);

	void updateVectors();

	void onParentMove(const glm::vec3& updatedPosition);

	inline glm::vec3 getForward() const { return forwardVector; }
	inline glm::vec3 getRight() const { return rightVector; }
};
