#pragma once

#include "GLFW/glfw3.h"
#include "InputMacros.h"

namespace wand
{
	enum class ButtonStatus { RELEASED = -1, PROCESSED = 0, PRESSED = 1 };

	class Input
	{
	public:
		/********************** Intended for the user *************************/
		static bool IsCapsLockOn();
		// Returns the number of times this key was checked if pressed, else 0 if released
		static ButtonStatus GetKeyStatus(int key);
		// Returns the number of times this button was checked if pressed, else 0 if released
		static ButtonStatus GetMouseButtonStatus(int button);
		static void GetMousePos(double& x, double& y);
		static double GetXScrollOffset();
		static double GetYScrollOffset();
		static bool IsMouseInArea(const float x, const float y, const float w, const float h);
		static void ProcessClick(int button);

		/********************* Intended for the engine ************************/
		static void SetupCallbacks(GLFWwindow* win);

	private:
		static const int MAX_KEYS;
		static const int MAX_MOUSE_BUTTONS;
		static bool capsLockOn;
		static ButtonStatus keys[];
		static ButtonStatus mouseButtons[];
		static double mouseXPos;
		static double mouseYPos;
		static double xScrollOffset;
		static double yScrollOffset;

		static void InitInput();
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
