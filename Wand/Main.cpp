#include "Window.h"

#include "glad/glad.c"

int main()
{
	wand::Window window;

	while (!window.IsClosed())
	{
		window.Update();
	}

	return 0;
}
