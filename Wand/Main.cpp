#include "WandPCH.h"
#include "glad/glad.c"

#include "Core/App.h"
#include "Graphics/Renderer.h"
#include "Graphics/Rectangle.h"

int main()
{
	wand::App app;
	
	glm::vec4 color1 = { 1.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 color2 = { 0.0f, 0.0f, 1.0f, 1.0f };

	std::shared_ptr<wand::Rectangle> rect = std::make_shared<wand::Rectangle>(color1);
	float width = rect.get()->GetWidth();
	float height = rect.get()->GetHeight();
	rect.get()->SetWidth(100.0f);
	rect.get()->SetHeight(100.0f);
	rect.get()->SetPosition(100.0f, 100.0f);


	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		//unsigned int count = 0;

		for (float x = 0.0f; x <= app.GetWidth(); x += width + 10.0f)
		{
			for (float y = 0.0f; y <= app.GetHeight(); y += height + 10.0f)
			{
				std::shared_ptr<wand::Rectangle> r = std::make_shared<wand::Rectangle>(color2);
				r.get()->SetPosition(x, y);
				wand::Renderer::Draw(r);
				//count++;
			}
		}
		wand::Renderer::Draw(rect);

		app.Update();

		//std::cout << "Rectangle count: " << count << std::endl;
		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}
