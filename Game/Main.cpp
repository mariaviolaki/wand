#include "Wand.h"

void fun()
{
	std::cout << "wand\n";
}

int main()
{
	wand::App app;

	wand::FontManager::Add(new wand::Font("arial", "C:\\Windows\\Fonts\\arial.ttf", 50));

	glm::vec4 rectColor = { 1.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 textColor = { 0.0f, 1.0f, 1.0f, 0.6f };
	float rectSize = 50.0f;
	float spriteSize = 100.0f;
	
	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		
		std::vector<std::shared_ptr<wand::Drawable>> drawables;

		// Render solid-color rectangles
		for (float x = 0.0f; x <= wand::Window::GetWidth(); x += rectSize + 10.0f)
		{
			for (float y = 0.0f; y <= wand::Window::GetHeight(); y += rectSize + 10.0f)
			{
				std::shared_ptr<wand::Rectangle> r = std::make_shared<wand::Rectangle>(rectColor);
				r->SetPosition(x, y);
				r->SetWidth(rectSize);
				r->SetHeight(rectSize);
				drawables.emplace_back(r);
				r->OnClick(fun);
				r->Show();
			}
		}

		/*
		// Render transparent and non-transparent sprites
		for (int x = 0; x < wand::Window::GetWidth(); x += spriteSize + 50.0f)
		{
			for (int y = 0; y < wand::Window::GetHeight(); y += spriteSize + 50.0f)
			{
				float rem = y % 20;
				std::string path = "Images\\wand." + std::string((rem == 0) ? "jpg" : "png");
				std::shared_ptr<wand::Sprite> s = std::make_shared<wand::Sprite>(path);
				s->SetPosition(x, y);
				drawables.emplace_back(s);
				s->OnClick(fun);
				s->Show();
			}
		}
		
		// Render semi-transparent text
		std::shared_ptr<wand::Text> text = std::make_shared<wand::Text>("arial", 50, textColor);
		text->SetPosition(0, 0);
		text->SetWidth(wand::Window::GetWidth());
		text->SetHeight(wand::Window::GetHeight());
		for (int i = 0; i < 10; i++)
		{
			text->Add("The quick brown fox jumps over the lazy dog. 1234567890 ");
		}

		drawables.emplace_back(text);
		text->Hide();
		text->OnClick(fun);
		text->Show();
		*/
		app.Update();

		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}
