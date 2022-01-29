#include "WandPCH.h"
#include "glad/glad.c"

#include "Core/App.h"
#include "Graphics/Renderer.h"
#include "Graphics/Rectangle.h"
#include "Graphics/Sprite.h"

int main()
{
	wand::App app;
	
	glm::vec4 color = { 1.0f, 0.0f, 1.0f, 1.0f };
	float rectSize = 10.0f;
	float spriteSize = 100.0f;
	
	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		std::vector<std::shared_ptr<wand::Rectangle>> rects;
		// Render solid-color rectangles
		for (float x = 0.0f; x <= app.GetWidth(); x += rectSize + 10.0f)
		{
			for (float y = 0.0f; y <= app.GetHeight(); y += rectSize + 10.0f)
			{
				std::shared_ptr<wand::Rectangle> r = std::make_shared<wand::Rectangle>(color);
				r->SetPosition(x, y);
				rects.emplace_back(r);
				wand::Renderer::Draw(r.get());
			}
		}
		
		std::vector<std::shared_ptr<wand::Sprite>> sprites;
		// Render transparent and non-transparent sprites
		for (int x = 0; x < app.GetWidth(); x += spriteSize + 50.0f)
		{
			for (int y = 0; y < app.GetHeight(); y += spriteSize + 50.0f)
			{
				float rem = y % 20;
				std::string path = "Images/wand." + std::string((rem == 0) ? "jpg" : "png");
				std::shared_ptr<wand::Sprite> s = std::make_shared<wand::Sprite>(path);
				s->SetPosition(x, y);
				s->SetWidth(spriteSize);
				s->SetHeight(spriteSize);
				sprites.emplace_back(s);
				wand::Renderer::Draw(s.get());
			}
		}

		app.Update();

		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}
