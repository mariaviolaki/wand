#include "Window.h"

int main()
{
	wand::Window window;

	while (!window.IsClosed())
	{
		window.Update();
	}

	return 0;
}
