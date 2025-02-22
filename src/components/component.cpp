#include "components/component.h"

#include <glm/detail/func_geometric.inl>

#include "glm/trigonometric.hpp"

Component::Component(const glm::vec3 inPos,
	const int inPitch,
	const int inYaw) : position(inPos),
	pitch(inPitch),
	yaw(inYaw)
{
	upVector = glm::vec3(0, 1, 0);
	rightVector = glm::vec3(1, 0, 0);
	forwardVector = glm::vec3(0, 0, -1);
}

void Component::rotateUp(const float delta)
{
	pitch += delta;
}

void Component::rotateRight(const float delta)
{
	yaw += delta;
}

void Component::rotate(const glm::vec2 delta) {
	rotateRight(delta.x);
	rotateUp(delta.y);
}

void Component::updateVectors()
{
	forwardVector.x = glm::cos(yaw) * glm::cos(pitch);
	forwardVector.y = glm::sin(pitch);
	forwardVector.z = glm::sin(yaw) * glm::cos(pitch);
	forwardVector = glm::normalize(forwardVector);

	rightVector = glm::normalize(glm::cross(forwardVector, glm::vec3(0, 1, 0)));
	upVector = glm::normalize(glm::cross(rightVector, forwardVector));
}

void Component::onParentMove(const glm::vec3& updatedPosition)
{
	position = updatedPosition;
}
