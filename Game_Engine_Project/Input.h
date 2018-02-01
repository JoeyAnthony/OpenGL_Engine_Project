#pragma once
#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "Vec.h"
#include <glm\glm.hpp>

#define KEYBOARD_KEY_ESC 27

namespace Keyboard
{
	const bool* GetKeyboard();
	const bool GetKey(int key);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

namespace Mouse
{
	glm::vec2 GetMousePos();
	const bool GetButton(int key);

	void MouseCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseEnterCallback(GLFWwindow* window, int entered);
}