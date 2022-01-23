#include "Window.h"
#include "glad/glad.c"
#include "Graphics/Renderer.h"

#include <iostream>
#include <chrono>

int main()
{
	wand::Window window;
	
	glm::vec2 pos;
	glm::vec2 dimens = { 0.02f, 0.02f };
	glm::vec4 color = { 0.0f, 0.0f, 1.0f, 1.0f };

	while (!window.IsClosed())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		//unsigned int count = 0;

		for (float x = -1.0f; x <= 1.0f; x += 0.03)
		{
			for (float y = -1.0f; y <= 1.0f; y += 0.03)
			{
				pos = { x, y };
				wand::Renderer::DrawRect(pos, dimens, color);
				//count++;
			}
		}

		window.Update();

		//std::cout << "Rectangle count: " << count << std::endl;
		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}
