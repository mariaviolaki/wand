#pragma once

#include "GLFW/glfw3.h"
#include "Core/Window.h"

namespace wand
{
	enum class ButtonStatus { RELEASED = -1, PROCESSED = 0, PRESSED = 1 };

	class InputManager
	{
	public:
		InputManager();
		void Init(GLFWwindow* window);

	private:
		GLFWwindow* mWindow;

		void SetupCallbacks();
	};
}
