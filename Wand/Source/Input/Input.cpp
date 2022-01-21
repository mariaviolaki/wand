#include "Input.h"

namespace // Only accessible in this file
{
	bool capsLockOn = false;
	const int MAX_KEYS = 400;
	const int MAX_MOUSE_BUTTONS = 10;
	bool keys[MAX_KEYS];
	bool mouseButtons[MAX_MOUSE_BUTTONS];
	double mouseXPos = 0.0;
	double mouseYPos = 0.0;
	double xScrollOffset = 0.0;
	double yScrollOffset = 0.0;

	// Set the initial state of input
	void InitInput()
	{
		// Set all keys to be released (false)
		for (int i = 0; i < MAX_KEYS; i++)
		{
			keys[i] = false;
		}

		// Set all mouse buttons to be released (false)
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			mouseButtons[i] = false;
		}
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			keys[key] = true;
		else // GLFW_RELEASE
			keys[key] = false;

		// Set the state of Caps Lock based on a bitwise [AND] operation
		capsLockOn = mods & GLFW_MOD_CAPS_LOCK;
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			mouseButtons[button] = true;
		else // GLFW_RELEASE
			mouseButtons[button] = false;
	}

	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseXPos = xpos;
		mouseYPos = ypos;
	}

	void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		xScrollOffset = xoffset;
		yScrollOffset = yoffset;
	}
}

/**************************************************************************************/

namespace wand::InputManager // compile with C++17 at least
{
	void SetupCallbacks(GLFWwindow* win)
	{
		InitInput();
		// Allow checking the state of Caps Lock
		glfwSetInputMode(win, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetKeyCallback(win, KeyCallback);
		glfwSetMouseButtonCallback(win, MouseButtonCallback);
		glfwSetCursorPosCallback(win, CursorPositionCallback);
		glfwSetScrollCallback(win, ScrollCallback);
	}
}

/**************************************************************************************/

namespace wand::Input // compile with C++17 at least
{
	bool IsCapsLockOn()
	{
		return capsLockOn;
	}

	bool IsKeyPressed(int key)
	{
		return keys[key];
	}

	bool IsMouseButtonPressed(int button)
	{
		return mouseButtons[button];
	}

	void GetMousePos(double& x, double& y)
	{
		x = mouseXPos;
		y = mouseYPos;
	}

	double GetXScrollOffset()
	{
		double offset = xScrollOffset;
		xScrollOffset = 0; // reset to 0
		return offset;
	}

	double GetYScrollOffset()
	{
		double offset = yScrollOffset;
		yScrollOffset = 0; // reset to 0
		return offset;
	}
}
