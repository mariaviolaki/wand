#include "Wand.h"

void fun1() { std::cout << "wand 1\n"; }
void fun2() { std::cout << "wand 2\n"; }

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

		// Create a layout - container for the rectangles
		std::shared_ptr<wand::Layout> layout = std::make_shared<wand::Layout>();
		layout->SetPosition(100, 100);
		layout->SetWidth(200);
		layout->SetHeight(200);
		// Create a rectangle with the same transform data as the layout
		std::shared_ptr<wand::Rectangle> rect = std::make_shared<wand::Rectangle>();
		rect->SetPosition(layout->GetPosition().x, layout->GetPosition().y);
		rect->SetWidth(layout->GetWidth());
		rect->SetHeight(layout->GetHeight());
		rect->SetDepth(-1);
		rect->Enable();
		rect->OnClick(fun1);
		rect->Show();
		
		// Render solid-color rectangles
		for (float x = 0.0f; x <= layout->GetWidth(); x += rectSize + 10.0f)
		{
			for (float y = 0.0f; y <= layout->GetHeight(); y += rectSize + 10.0f)
			{
				std::shared_ptr<wand::Rectangle> r = std::make_shared<wand::Rectangle>(rectColor);
				r->SetDepth(1);
				r->SetParentLayout(layout);
				//r->SetPosition(x, y);
				r->SetWidth(rectSize);
				r->SetHeight(rectSize);
				//r->SetLayoutPosition(x, y);
				r->SetLayoutPosition(wand::LayoutPosition::CENTERX, wand::LayoutPosition::CENTERY);
				drawables.emplace_back(r);
				r->Enable();
				r->OnClick(fun2);
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
