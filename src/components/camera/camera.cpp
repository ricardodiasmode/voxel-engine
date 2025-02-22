//
// Created by ricar on 2/21/2025.
//

#include "components/camera/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>


Camera::Camera(const glm::vec3 inPos,
               const float inPitch,
               const float inYaw) : Component(inPos,
                                              inPitch,
                                              inYaw)

{
	proj = glm::perspective<float>(VERTICAL_FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
}

void Camera::updateViewMatrix()
{
	view = glm::lookAt(position, position + forwardVector, upVector);
}

void Camera::update()
{
	updateVectors();
	updateViewMatrix();
}

void Camera::rotateUp(const float delta)
{
	Component::rotateUp(-delta);
	pitch = glm::clamp(pitch, -MAX_PITCH, MAX_PITCH);
}
