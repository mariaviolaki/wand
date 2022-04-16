#include "WandPCH.h"
#include "InputManager.h"
#include "Events/Event.h"

namespace wand
{
	InputManager::InputManager()
		: mWindow(nullptr)
	{}

	void InputManager::Init(GLFWwindow* window)
	{
		mWindow = window;
		// Allow checking the state of Caps Lock
		glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		SetupCallbacks();
	}

	void InputManager::SetupCallbacks()
	{
		// Keypress callback
		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// Set the state of Caps Lock based on a bitwise [AND] operation
			bool capsOn = mods & GLFW_MOD_CAPS_LOCK;

			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
			{
				KeyDownEvent* event = new KeyDownEvent(key, capsOn);
				data->EventCallback(event);
			}
			else if (action == GLFW_RELEASE)
			{
				KeyUpEvent* event = new KeyUpEvent(key, capsOn);
				data->EventCallback(event);
			}
		});

		// Mouse button click callback
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
			{
				MouseButtonDownEvent* event = new MouseButtonDownEvent(button);
				data->EventCallback(event);
			}
			else if (action == GLFW_RELEASE)
			{
				MouseButtonUpEvent* event = new MouseButtonUpEvent(button);
				data->EventCallback(event);
			}
		});

		// Mouse scroll callback
		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			if (yoffset == 0.0)
			{
				MouseScrollXEvent* event = new MouseScrollXEvent(xoffset);
				data->EventCallback(event);
			}
			else if (xoffset == 0.0)
			{
				MouseScrollYEvent* event = new MouseScrollYEvent(yoffset);
				data->EventCallback(event);
			}
		});

		// Mouse move callback
		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			// Find the offsets to the beginning of the window with the correct aspect ratio
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			float xOffset = (width - data->width) / 2;
			float yOffset = (height - data->height) / 2;
			// Invert the Y axis to use the bottom edge as origin
			MouseMoveEvent* event = new MouseMoveEvent(xpos - xOffset, data->height - ypos + yOffset);
			data->EventCallback(event);
		});
	}
}
