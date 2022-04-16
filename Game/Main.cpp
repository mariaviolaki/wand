#include "Wand.h"
//#include <thread>
//#include <chrono>

void playSound(wand::App& app, wand::Rectangle& r)
{
	std::cout << r.GetLabel() << ": x=" << r.GetTransform().GetPosition().x
		<< ", y=" << r.GetTransform().GetPosition().y
		<< ", width=" << r.GetTransform().GetWidth()
		<< ", height=" << r.GetTransform().GetHeight() << std::endl;
	app.GetAudioManager()->Play("tick");
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//app.GetAudioManager()->Stop("tick");
}
void loadData(wand::App& app);

int main()
{
	wand::App app;

	loadData(app);

	wand::Rectangle& r1 = app.GetEntityManager()->AddRectangle({ 1.0f, 0.0f, 0.0f, 1.0f });

	r1.GetTransform().SetDepth(6);
	r1.GetTransform().SetPosition(100, 100);
	r1.GetTransform().SetWidth(100);
	r1.GetTransform().SetHeight(100);
	r1.OnLeftClick([&app, &r1]() { playSound(app, r1); });
	r1.SetLabel("red square");
	r1.Enable();
	r1.Show();

	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		app.Clear();

		wand::Input& input = app.GetInput();
		if (input.MouseButtonDown(MOUSE_BUTTON_LEFT))
			std::cout << "(" << input.GetX() << ", " << input.GetY() << ")\n";
		
		app.Update();
		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}
	return 0;
}

void loadData(wand::App& app)
{
	app.GetFontManager()->Add("C:\\Windows\\Fonts\\arial.ttf", "arial", 20);
	app.GetAudioManager()->Add("Audio/tick.ogg", "tick");
	wand::Window& window = app.GetWindow();

	glm::vec4 rectColor = { 1.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 textColor = { 0.0f, 1.0f, 1.0f, 0.6f };
	float rectSize = 100.0f;
	float spriteSize = 200.0f;

	// Create a layout - container for the rectangles
	std::shared_ptr<wand::Layout> layout = std::make_shared<wand::Layout>();
	layout->SetPosition(100, 100);
	layout->SetWidth(200);
	layout->SetHeight(200);

	// Create a rectangle with the same transform data as the layout
	wand::Rectangle& rect = app.GetEntityManager()->AddRectangle({ 1.0f, 1.0f, 1.0f, 0.5f });
	rect.GetTransform().SetPosition(layout->GetPosition().x, layout->GetPosition().y);
	rect.GetTransform().SetWidth(layout->GetWidth());
	rect.GetTransform().SetHeight(layout->GetHeight());
	rect.GetTransform().SetDepth(4);
	rect.OnLeftClick([&app, &rect]() { playSound(app, rect); });
	rect.SetLabel("transparent white square");
	rect.Enable();
	rect.Show();
	
	// Render solid-color rectangles
	for (float x = 0.0f; x <= layout->GetWidth(); x += rectSize + 10.0f)
	{
		for (float y = 0.0f; y <= layout->GetHeight(); y += rectSize + 10.0f)
		{
			wand::Rectangle& r = app.GetEntityManager()->AddRectangle(rectColor);
			r.GetTransform().SetDepth(5);
			r.SetParentLayout(layout);
			//r.SetPosition(x, y);
			r.GetTransform().SetWidth(rectSize);
			r.GetTransform().SetHeight(rectSize);
			r.SetLayoutPosition(x, y);
			r.SetLabel("pink square");
			r.OnLeftClick([&app, &r]() { playSound(app, r); });
			//r.SetLayoutPosition(wand::LayoutPosition::CENTERX, wand::LayoutPosition::CENTERY);
			r.Enable();
			r.Show();
		}
	}

	// Render transparent and non-transparent sprites
	for (int x = 0; x < window.GetWidth(); x += spriteSize + 15.0f)
	{
		for (int y = 0; y < window.GetHeight(); y += spriteSize + 15.0f)
		{
			float rem = y % 2;
			std::string path = "Images\\wand." + std::string((rem == 0) ? "jpg" : "png");
			wand::Sprite& s = app.GetEntityManager()->AddSprite(path);
			s.GetTransform().SetPosition(x, y);
			s.GetTransform().SetDepth(3);
			s.GetTransform().SetWidth(100);
			s.GetTransform().SetHeight(100);
			s.Show();
		}
	}
	
	// Render semi-transparent text
	wand::Text& t1 = app.GetEntityManager()->AddText("arial", 20, textColor);
	t1.GetTransform().SetPosition(0, 0);
	t1.GetTransform().SetDepth(1);
	t1.GetTransform().SetWidth(window.GetWidth());
	t1.GetTransform().SetHeight(window.GetHeight());
	for (int i = 0; i < 50; i++)
	{
		t1.Add("The quick brown fox jumps over the lazy dog. ");
	}
	t1.Show();
}
