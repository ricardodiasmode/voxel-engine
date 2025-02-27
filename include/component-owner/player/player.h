#pragma once
#include <memory>
#include <components/camera/camera.h>

#include "playerInput.h"
#include "component-owner/componentOwner.h"

class Player : public ComponentOwner {
	static constexpr auto PLAYER_VELOCITY = 0.1f;
	static constexpr auto MOUSE_SENSITIVITY = 0.005f;

private:
	std::shared_ptr<Camera> playerCamera;
	std::unique_ptr<PlayerInput> playerInput;

	glm::vec3 position = glm::vec3(0);

private:
	void move(const glm::vec3 direction);

	void moveForward();

	void moveBackwards();

	void moveRight();

	void moveLeft();

	void mapKeyboard();

public:
	Player(GLFWwindow* window);

	glm::mat4 getView() const;
	glm::mat4 getProj() const;

	void update();
};
