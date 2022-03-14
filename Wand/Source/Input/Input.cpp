#include "WandPCH.h"
#include "Input.h"
#include "Core/Window.h"

namespace wand
{
	const int Input::MAX_KEYS = 400;
	const int Input::MAX_MOUSE_BUTTONS = 10;
	bool Input::capsLockOn = false;
	ButtonStatus Input::keys[MAX_KEYS];
	ButtonStatus Input::mouseButtons[MAX_MOUSE_BUTTONS];
	double Input::mouseXPos = 0.0;
	double Input::mouseYPos = 0.0;
	double Input::xScrollOffset = 0.0;
	double Input::yScrollOffset = 0.0;

	/************************ PUBLIC FUNCTIONS *****************************/

	bool Input::IsCapsLockOn()
	{
		return capsLockOn;
	}

	ButtonStatus Input::GetKeyStatus(int key)
	{
		ButtonStatus status = keys[key];
		if (keys[key] == ButtonStatus::PRESSED)
			keys[key] = ButtonStatus::PROCESSED;
		return status;
	}

	ButtonStatus Input::GetMouseButtonStatus(int button)
	{
		return mouseButtons[button];
	}

	void Input::GetMousePos(double& x, double& y)
	{
		x = mouseXPos;
		y = mouseYPos;
	}

	double Input::GetXScrollOffset()
	{
		double offset = xScrollOffset;
		xScrollOffset = 0; // reset to 0
		return offset;
	}

	double Input::GetYScrollOffset()
	{
		double offset = yScrollOffset;
		yScrollOffset = 0; // reset to 0
		return offset;
	}

	bool Input::IsMouseInArea(const float x, const float y, const float w, const float h)
	{
		double currentX, currentY;
		GetMousePos(currentX, currentY);

		return currentX >= x && currentX <= x + w
			&& currentY >= y && currentY <= y + h;
	}

	void Input::ProcessClick(int button)
	{
		// Mark button as processed to prevent triggering additional functions
		mouseButtons[button] = ButtonStatus::PROCESSED;
	}

	void Input::SetupCallbacks(GLFWwindow* win)
	{
		InitInput();
		// Allow checking the state of Caps Lock
		glfwSetInputMode(win, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetKeyCallback(win, KeyCallback);
		glfwSetMouseButtonCallback(win, MouseButtonCallback);
		glfwSetCursorPosCallback(win, CursorPositionCallback);
		glfwSetScrollCallback(win, ScrollCallback);
	}

	/************************ PRIVATE FUNCTIONS *****************************/

	// Set the initial state of input
	void Input::InitInput()
	{
		// Set all keys to be released
		for (int i = 0; i < MAX_KEYS; i++)
		{
			keys[i] = ButtonStatus::RELEASED;
		}

		// Set all mouse buttons to be released
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			mouseButtons[i] = ButtonStatus::RELEASED;
		}
	}

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			keys[key] = ButtonStatus::PRESSED;
		else if (action == GLFW_RELEASE)
			keys[key] = ButtonStatus::RELEASED;

		// Set the state of Caps Lock based on a bitwise [AND] operation
		capsLockOn = mods & GLFW_MOD_CAPS_LOCK;
	}

	void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
			mouseButtons[button] = ButtonStatus::PRESSED;
		else if (action == GLFW_RELEASE)
			mouseButtons[button] = ButtonStatus::RELEASED;
	}

	void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseXPos = xpos;
		// Invert the Y axis to use the bottom edge as origin
		mouseYPos = Window::GetHeight() - ypos;
	}

	void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		xScrollOffset = xoffset;
		yScrollOffset = yoffset;
	}
}
