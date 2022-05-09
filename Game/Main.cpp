#include "Wand.h"
#include <chrono>

void toggleFullscreen(wand::App& app)
{
	auto window = app.GetWindow();
	if (window->IsFullscreen())
		window->SetFullscreen(false);
	else
		window->SetFullscreen(true);
}
void exitApp(wand::App& app)
{
	app.Exit();
}
void showMousePos(wand::App& app)
{
	wand::Input* input = app.GetInput();
	std::string mousePos = "Mouse Pos: [" + std::to_string(input->GetX()) + ", " + std::to_string(input->GetY()) + "]\n";
	wand::Logger::Log(mousePos);
}
void loadData(std::shared_ptr<wand::App> app); // pass app copy for valid lambda functions

// Entry point for windows applications
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	std::shared_ptr<wand::App> app = std::make_shared<wand::App>();
	std::string gameDir = app->GetFileManager()->GetRootFolder() + "Game\\";
	
	loadData(app);

	wand::Logger::Log("Random Numbers: [ ");
	for (int i = 0; i < 10; i++)
	{
		wand::Logger::Log(std::to_string(wand::Random::GetInt(0, 10)) + " ");
	}
	wand::Logger::Log("]\n");
	
	// Test rectangle rendering and events
	wand::Rectangle& r1 = app->GetEntityManager()->AddRectangle(wand::Color(255, 0, 0, 255));
	r1.GetTransform()->SetDepth(3);
	r1.GetTransform()->SetPos(100, 100);
	r1.GetTransform()->SetWidth(100);
	r1.GetTransform()->SetHeight(100);
	r1.OnLeftClick([&app]() { toggleFullscreen(*app.get()); });
	r1.OnRightClick([&app]() { exitApp(*app.get()); });
	r1.OnHover([&app]() { showMousePos(*app.get()); });
	r1.SetLabel("red square");
	r1.Enable();
	
	// Test buttons
	wand::Color buttonColor(127, 255, 255, 255);
	wand::Color textColor(50, 50, 50, 255);
	wand::Button& button = app->GetEntityManager()->AddButton(gameDir + "Images\\button.png", "arial", 20, textColor);
	button.GetTransform()->SetWidth(200);
	button.GetTransform()->SetHeight(100);
	button.SetText("Click me!");
	button.GetTransform()->SetDepth(4);
	button.SetLabel("green button");
	button.OnLeftClick([&app]() { toggleFullscreen(*app); });
	button.OnRightClick([&app]() { exitApp(*app); });
	button.OnHover([&app]() { showMousePos(*app); });
	
	while (app->IsRunning())
	{
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		app->Clear();

		app->Update();
		std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//wand::Logger::Log(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) + " ms\n");
	}
	return 0;
}

void loadData(std::shared_ptr<wand::App> app)
{
	std::string gameDir = app->GetFileManager()->GetRootFolder() + "Game\\";
	app->GetFontManager()->Add("C:\\Windows\\Fonts\\arial.ttf", "arial", 20);
	app->GetFontManager()->Add("C:\\Windows\\Fonts\\arialbd.ttf", "arialbd", 20);
	app->GetAudioManager()->Add(gameDir + "Audio\\tick.ogg", "tick");
	wand::Window* window = app->GetWindow();

	wand::Color rectColor(255, 0, 255, 255);
	wand::Color textColor(0, 255, 255, 130);
	float rectSize = 100.0f;
	float spriteSize = 200.0f;

	// Create a layout - container for the rectangles
	wand::Rectangle& layout = app->GetEntityManager()->AddRectangle();
	layout.GetTransform()->SetPos(0, 0);
	layout.GetTransform()->SetWidth(window->GetWidth());
	layout.GetTransform()->SetHeight(window->GetHeight());
	layout.GetTransform()->SetDepth(1);
	layout.Hide();
	
	std::vector<wand::Rectangle> rects;
	for (int i = 0; i < 10; i++)
	{
		auto& r = app->GetEntityManager()->AddRectangle(rectColor);
		rects.emplace_back(r);
		r.SetParentLayout(layout.GetTransform());
		r.GetTransform()->SetWidth(rectSize);
		r.GetTransform()->SetHeight(rectSize);
		r.SetLabel("pink square " + std::to_string(i));
		r.OnLeftClick([&app]() { toggleFullscreen(*app); });
		r.OnRightClick([&app]() { exitApp(*app); });
		r.OnHover([&app]() { showMousePos(*app); });
		r.Enable();
	}

	rects[0].SetLayoutPosition(wand::LayoutPosition::LEFT, wand::LayoutPosition::TOP);
	rects[1].SetLayoutPosition(wand::LayoutPosition::LEFT, wand::LayoutPosition::MIDTOP);
	rects[2].SetLayoutPosition(wand::LayoutPosition::LEFT, wand::LayoutPosition::MIDDLEY);
	rects[3].SetLayoutPosition(wand::LayoutPosition::LEFT, wand::LayoutPosition::MIDBOTTOM);
	rects[4].SetLayoutPosition(wand::LayoutPosition::LEFT, wand::LayoutPosition::BOTTOM);
	rects[5].SetLayoutPosition(wand::LayoutPosition::MIDLEFT, wand::LayoutPosition::BOTTOM);
	rects[6].SetLayoutPosition(wand::LayoutPosition::MIDDLEX, wand::LayoutPosition::BOTTOM);
	rects[7].SetLayoutPosition(wand::LayoutPosition::MIDRIGHT, wand::LayoutPosition::BOTTOM);
	rects[8].SetLayoutPosition(wand::LayoutPosition::RIGHT, wand::LayoutPosition::BOTTOM);
	
	// Render transparent and non-transparent sprites
	for (int x = 0; x < window->GetWidth(); x += spriteSize + 15.0f)
	{
		for (int y = 0; y < window->GetHeight(); y += spriteSize + 15.0f)
		{
			float rem = y % 2;
			std::string path = gameDir + "Images\\wand." + std::string((rem == 0) ? "jpg" : "png");
			wand::Sprite& s = app->GetEntityManager()->AddSprite(path);
			s.GetTransform()->SetPos(x, y);
			s.GetTransform()->SetDepth(0);
			s.GetTransform()->SetWidth(100);
			s.GetTransform()->SetHeight(100);
		}
	}
	
	// Render semi-transparent text
	wand::TextBox& t1 = app->GetEntityManager()->AddTextBox("arial", 20, textColor);
	t1.GetTransform()->SetPos(0, 0);
	t1.GetTransform()->SetDepth(5);
	t1.GetTransform()->SetWidth(window->GetWidth());
	t1.GetTransform()->SetHeight(window->GetHeight());
	std::string text = "";
	for (int i = 0; i < 100; i++)
	{
		text += "The quick brown fox jumps over the lazy dog. ";
	}
	t1.SetText(text);
}
