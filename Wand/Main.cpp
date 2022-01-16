#include "Window.h"

#include "glad/glad.c"
#include "Input.h"
#include <iostream>

int main()
{
	wand::Window window;

	while (!window.IsClosed())
	{
		// Check key press
		if (wand::Input::IsKeyPressed(KEY_E))
		{
			if (wand::Input::IsCapsLockOn())
				std::cout << "E pressed\n";
			else
				std::cout << "e pressed\n";
		}

		/*
		// Check mouse button press
		if (wand::Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			std::cout << "Left click\n";

		// Check mouse position
		double xPos;
		double yPos;
		wand::Input::GetMousePos(xPos, yPos);
		std::cout << "x = " << xPos << ", y = " << yPos << std::endl;

		// Check mouse scroll offset
		std::cout << wand::Input::GetYScrollOffset() << std::endl;
		*/

		window.Update();
	}

	return 0;
}
