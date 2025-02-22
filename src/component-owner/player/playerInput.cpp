#include "component-owner/player/playerInput.h"

#include <utils/debug.h>

#include "GLFW/glfw3.h"

PlayerInput::PlayerInput(GLFWwindow* window,
		const glm::vec2 currentMousePos) : lastMousePos(currentMousePos) {
	if (!window)
		return;

	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, PlayerInput::keyCallbackStatic);

	glfwSetCursorPosCallback(window, PlayerInput::cursorCallbackStatic);

	windowRef = window;
}

void PlayerInput::keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (PlayerInput* instance = static_cast<PlayerInput*>(glfwGetWindowUserPointer(window))) {
		instance->keyCallback(window, key, scancode, action, mods);
	}
}

void PlayerInput::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (mappedKeys.contains({key, action}) && mappedKeys[{key, action}]) {
		if (debug)
			print("PlayerInput calling key callback: " << key);
		mappedKeys[{key, action}]();
	}
}

void PlayerInput::cursorCallbackStatic(GLFWwindow * window, double xpos, double ypos)
{
	if (PlayerInput* instance = static_cast<PlayerInput*>(glfwGetWindowUserPointer(window))) {
		instance->cursorCallback(window, xpos, ypos);
	}
}

void PlayerInput::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
	if (mouseMoveCallback) {
		if (debug)
			print("PlayerInput calling mouse callback!");

		mouseMoveCallback(glm::vec2(xpos, ypos) - lastMousePos);
	}

	lastMousePos = glm::vec2(xpos, ypos);
}

void PlayerInput::mapKey(const int key, const int action, const std::function<void()> &callback) {
	if (debug)
		print("PlayerInput mapping key: " << key);

	mappedKeys[{key, action}] = callback;
}

void PlayerInput::update() {
	if (!windowRef)
		return;

	for (const auto& [inputData, callback] : mappedKeys) {
		if (glfwGetKey(windowRef, inputData.key) == GLFW_PRESS &&
			inputData.action == GLFW_PRESS) {
			callback();
		}
	}
}
