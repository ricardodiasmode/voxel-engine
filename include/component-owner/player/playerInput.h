#pragma once
#include <functional>
#include <map>
#include <glm/vec2.hpp>

#include "GLFW/glfw3.h"

struct InputData {
	int key = -1;
	int action = -1;

	InputData(const int inKey, const int inAction) : key(inKey), action(inAction) {};

	bool operator==(const InputData &other) const {
		return key == other.key && action == other.action;
	}
	bool operator<(const InputData &other) const {
		return key < other.key || (key == other.key && action < other.action);
	}
};

class PlayerInput {
private:
	bool debug = false;

	GLFWwindow* windowRef = nullptr;

public:
	std::map<InputData, std::function<void()>> mappedKeys;
	std::function<void(const glm::vec2& delta)> mouseMoveCallback;

	glm::vec2 lastMousePos;

public:

	PlayerInput(GLFWwindow* window,
		const glm::vec2 currentMousePos);

	static void cursorCallbackStatic(GLFWwindow * window, double xpos, double ypos);

	static void keyCallbackStatic(GLFWwindow *window, int key, int scancode, int action, int mods);

	void cursorCallback(GLFWwindow * window, double xpos, double ypos);

	void keyCallback(GLFWwindow* window,
	                  int key,
	                  int scancode,
	                  int action,
	                  int mods);

	void mapKey(const int key, const int action, const std::function<void()>& callback);

	void update();
};
