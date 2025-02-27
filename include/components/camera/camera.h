//
// Created by ricar on 2/21/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <components/component.h>

#include "window/window.h"
#include <glm/glm.hpp>

class Camera : public Component {
public:
	static constexpr auto ASPECT_RATIO = Window::WIDTH/Window::HEIGHT;
	static constexpr auto FOV = 50.f;
	static constexpr auto VERTICAL_FOV = glm::radians(FOV);
	static constexpr auto NEAR_PLANE = 0.1f;
	static constexpr auto FAR_PLANE = 2000.f;
	static constexpr auto MAX_PITCH = glm::radians(89.f);
	const float HORIZONTAL_FOV = 2.f * atan(tan(VERTICAL_FOV * 0.5f) * ASPECT_RATIO);

private:

	glm::mat4 proj = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);

private:
	void updateViewMatrix();

public:
	Camera(const glm::vec3 inPos,
		const float inPitch,
		const float inYaw);

	void update();

	virtual void rotateUp(const float delta) override;

	inline glm::mat4 getView() const { return view; }
	inline glm::mat4 getProj() const { return proj; }
};



#endif //CAMERA_H
