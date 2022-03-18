#include "Wand.h"

void fun1() { std::cout << "wand 1\n"; }
void fun2() { std::cout << "wand 2\n"; }
void loadData(wand::App& app);

int main()
{
	wand::App app;

	loadData(app);

	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

		app.Update();

		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}

	return 0;
}

void loadData(wand::App& app)
{
	wand::FontManager::Add(new wand::Font("arial", "C:\\Windows\\Fonts\\arial.ttf", 50));
	wand::FontManager::Add(new wand::Font("arialbd", "C:\\Windows\\Fonts\\arialbd.ttf", 50));

	glm::vec4 rectColor = { 1.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 textColor = { 0.0f, 1.0f, 1.0f, 0.6f };
	float rectSize = 50.0f;
	float spriteSize = 100.0f;

	// Create a layout - container for the rectangles
	std::shared_ptr<wand::Layout> layout = std::make_shared<wand::Layout>();
	layout->SetPosition(100, 100);
	layout->SetWidth(200);
	layout->SetHeight(200);

	// Create a rectangle with the same transform data as the layout
	wand::Rectangle& rect = (wand::Rectangle&)app.AddEntity(new wand::Rectangle({1.0f, 1.0f, 1.0f, 0.5f}));
	rect.GetTransform().SetPosition(layout->GetPosition().x, layout->GetPosition().y);
	rect.GetTransform().SetWidth(layout->GetWidth());
	rect.GetTransform().SetHeight(layout->GetHeight());
	rect.GetTransform().SetDepth(3);
	rect.Enable();
	rect.OnClick(fun1);
	rect.Show();
	
	// Render solid-color rectangles
	for (float x = 0.0f; x <= layout->GetWidth(); x += rectSize + 10.0f)
	{
		for (float y = 0.0f; y <= layout->GetHeight(); y += rectSize + 10.0f)
		{
			wand::Rectangle& r = (wand::Rectangle&)app.AddEntity(new wand::Rectangle(rectColor));
			r.GetTransform().SetDepth(4);
			r.SetParentLayout(layout);
			//r.SetPosition(x, y);
			r.GetTransform().SetWidth(rectSize);
			r.GetTransform().SetHeight(rectSize);
			r.SetLayoutPosition(x, y);
			//r.SetLayoutPosition(wand::LayoutPosition::CENTERX, wand::LayoutPosition::CENTERY);
			r.Enable();
			r.OnClick(fun2);
			r.Show();
		}
	}

	// Render transparent and non-transparent sprites
	for (int x = 0; x < wand::Window::GetWidth(); x += spriteSize + 15.0f)
	{
		for (int y = 0; y < wand::Window::GetHeight(); y += spriteSize + 15.0f)
		{
			float rem = y % 2;
			std::string path = "Images\\wand." + std::string((rem == 0) ? "png" : "jpg");
			wand::Sprite& s = (wand::Sprite&)app.AddEntity(new wand::Sprite(path));
			s.GetTransform().SetPosition(x, y);
			s.GetTransform().SetDepth(0);
			s.OnClick(fun1);
			s.Show();
		}
	}
	
	// Render semi-transparent text
	wand::Text& t1 = (wand::Text&)app.AddEntity(new wand::Text("arialbd", 50, textColor));
	t1.GetTransform().SetPosition(0, 0);
	t1.GetTransform().SetDepth(1);
	t1.GetTransform().SetWidth(wand::Window::GetWidth());
	t1.GetTransform().SetHeight(wand::Window::GetHeight());
	for (int i = 0; i < 10; i++)
	{
		t1.Add("The quick brown fox jumps over the lazy dog. ");
	}
	t1.OnClick(fun1);
	t1.Show();
	
	wand::Text& t2 = (wand::Text&)app.AddEntity(new wand::Text("arial", 50, rectColor));
	t2.GetTransform().SetPosition(0, 0);
	t2.GetTransform().SetDepth(2);
	t2.GetTransform().SetWidth(wand::Window::GetWidth());
	t2.GetTransform().SetHeight(wand::Window::GetHeight());
	for (int i = 0; i < 30; i++)
	{
		t2.Add("1234567890 ");
	}
	t2.OnClick(fun1);
	t2.Show();
}
