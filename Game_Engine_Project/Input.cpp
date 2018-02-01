// #include "Component.h"
#include "Input.h"
/*
* bool arrays, are read by components
*/

bool keyboard[255];

glm::vec2 mousePos;
bool mouse[255];

//http://www.glfw.org/docs/latest/input_guide.html#events

/*
* returns keyboard array as constant pointer
*/
const bool * Keyboard::GetKeyboard()
{
	return keyboard;
}

const bool Keyboard::GetKey(int key)
{
	return keyboard[key];
}


void Keyboard::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	keyboard[key] = action;

	if (key == GLFW_KEY_ESCAPE)
	{
		glfwTerminate();
		exit(0);
	}
}

/*
* returns mouseposition as const pointer
*/
glm::vec2 Mouse::GetMousePos()
{
	return mousePos;
}

const bool Mouse::GetButton(int key)
{
	return mouse[key];
}

/*
* set mouse movement and updates coordinates
*/
void Mouse::MouseCursorPosCallback(GLFWwindow * window, double xpos, double ypos)
{
	mousePos = glm::vec2(xpos, ypos);
}

/*
* set mouse buttons
*/
void Mouse::MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	mouse[button] = action;
}

void Mouse::MouseEnterCallback(GLFWwindow * window, int entered)
{
	if (entered)
	{
	}
	else
	{
	}
}
