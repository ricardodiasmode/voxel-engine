#include "component-owner/player/player.h"

#include <utils/debug.h>
#include "world/chunk/chunk.h"

void Player::moveForward() {
	if (!playerCamera)
		return;
	move(glm::vec3(playerCamera->getForward() * PLAYER_VELOCITY));
}

void Player::moveBackwards() {
	if (!playerCamera)
		return;
	move(glm::vec3(playerCamera->getForward() * -PLAYER_VELOCITY));
}

void Player::moveRight() {
	if (!playerCamera)
		return;
	move(glm::vec3(playerCamera->getRight() * PLAYER_VELOCITY));
}

void Player::moveLeft() {
	if (!playerCamera)
		return;
	move(glm::vec3(playerCamera->getRight() * -PLAYER_VELOCITY));
}

void Player::mapKeyboard() {
	playerInput->mapKey(GLFW_KEY_W, GLFW_PRESS, [this] {
		moveForward();
	});
	playerInput->mapKey(GLFW_KEY_S, GLFW_PRESS, [this] {
		moveBackwards();
	});
	playerInput->mapKey(GLFW_KEY_D, GLFW_PRESS, [this] {
		moveRight();
	});
	playerInput->mapKey(GLFW_KEY_A, GLFW_PRESS, [this] {
		moveLeft();
	});
}

glm::mat4 Player::getView() const {
	return playerCamera->getView();
}

glm::mat4 Player::getProj() const {
	return playerCamera->getProj();
}

void Player::update() {
	if (!playerInput)
		return;
	playerInput->update();
	playerCamera->update();
}

Player::Player(GLFWwindow* window)
{
	position = glm::vec3(Chunk::HORIZONTAL_CHUNK_SIZE, Chunk::CHUNK_SIZE, Chunk::CHUNK_SIZE * 1.5);

	playerCamera = initializeComponent<Camera>(position,
		0.f,
		0.f);
	assert(playerCamera);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	playerInput = std::make_unique<PlayerInput>(window,
		glm::vec2(xpos, ypos));
	assert(playerInput);

	mapKeyboard();

	playerInput->mouseMoveCallback = [this](const glm::vec2& delta) {
		if (playerCamera) {
			playerCamera->rotate(delta * MOUSE_SENSITIVITY);
		}
	};
}

void Player::move(const glm::vec3 direction)
{
	position += direction * PLAYER_VELOCITY;
	updateComponentsLocation(position);
}
