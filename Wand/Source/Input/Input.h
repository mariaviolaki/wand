#pragma once

#include "GLFW/glfw3.h"
#include "InputMacros.h"

// Intended for the engine
namespace wand::InputManager
{
	void SetupCallbacks(GLFWwindow* win);
}

// Intended for the user
namespace wand::Input
{
	bool IsCapsLockOn();
	bool IsKeyPressed(int key);
	bool IsMouseButtonPressed(int button);
	void GetMousePos(double& x, double& y);
	double GetXScrollOffset();
	double GetYScrollOffset();
}
