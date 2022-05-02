#include "Wand.h"
//#include <thread>
//#include <chrono>

void toggleFullscreen(wand::App& app)
{
	if (app.GetWindow()->IsFullscreen())
		app.GetWindow()->SetFullscreen(false);
	else
		app.GetWindow()->SetFullscreen(true);
}
void exitApp(wand::App& app)
{
	app.Exit();
}
void showMousePos(wand::App& app)
{
	wand::Input* input = app.GetInput();
	std::cout << "Mouse Pos: [" << input->GetX() << ", " << input->GetY() << "]\n";
}
void loadData(wand::App& app);

int main()
{
	wand::App app;
	loadData(app);

	app.GetCursorManager()->CreateCursor(wand::CursorType::ARROW, "Images/arrow_cursor.png");
	app.GetCursorManager()->CreateCursor(wand::CursorType::HAND, "Images/hand_cursor.png");
	
	// Test rectangle rendering and events
	wand::Rectangle& r1 = app.GetEntityManager()->AddRectangle({ 1.0f, 0.0f, 0.0f, 1.0f });
	r1.GetTransform()->SetDepth(3);
	r1.GetTransform()->SetPos(100, 100);
	r1.GetTransform()->SetWidth(100);
	r1.GetTransform()->SetHeight(100);
	r1.OnLeftClick([&app]() { toggleFullscreen(app); });
	r1.OnRightClick([&app]() { exitApp(app); });
	r1.OnHover([&app]() { showMousePos(app); });
	r1.SetLabel("red square");
	r1.Enable();
	
	// Test buttons
	glm::vec4 buttonColor = { 0.5f, 1.0f, 1.0f, 1.0f };
	glm::vec4 textColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	wand::Button& button = app.GetEntityManager()->AddButton("Images/button.png", "arial", 20, textColor);
	button.GetTransform()->SetWidth(200);
	button.GetTransform()->SetHeight(100);
	button.SetText("Click me!");
	button.GetTransform()->SetDepth(4);
	button.SetLabel("green button");
	button.OnLeftClick([&app]() { toggleFullscreen(app); });
	button.OnRightClick([&app]() { exitApp( app); });
	button.OnHover([&app]() { showMousePos(app); });
	
	while (app.IsRunning())
	{
		//std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		app.Clear();

		app.Update();
		//std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
	}
	return 0;
}

void loadData(wand::App& app)
{
	app.GetFontManager()->Add("C:\\Windows\\Fonts\\arial.ttf", "arial", 20);
	app.GetFontManager()->Add("C:\\Windows\\Fonts\\arialbd.ttf", "arialbd", 20);
	app.GetAudioManager()->Add("Audio/tick.ogg", "tick");
	wand::Window* window = app.GetWindow();

	glm::vec4 rectColor = { 1.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 textColor = { 0.0f, 1.0f, 1.0f, 0.6f };
	float rectSize = 100.0f;
	float spriteSize = 200.0f;

	// Create a layout - container for the rectangles
	wand::Rectangle& layout = app.GetEntityManager()->AddRectangle();
	layout.GetTransform()->SetPos(0, 0);
	layout.GetTransform()->SetWidth(window->GetWidth());
	layout.GetTransform()->SetHeight(window->GetHeight());
	layout.GetTransform()->SetDepth(1);
	layout.Hide();
	
	std::vector<wand::Rectangle> rects;
	for (int i = 0; i < 10; i++)
	{
		auto& r = app.GetEntityManager()->AddRectangle(rectColor);
		rects.emplace_back(r);
		r.SetParentLayout(layout.GetTransform());
		r.GetTransform()->SetWidth(rectSize);
		r.GetTransform()->SetHeight(rectSize);
		r.SetLabel("pink square " + std::to_string(i));
		r.OnLeftClick([&app]() { toggleFullscreen(app); });
		r.OnRightClick([&app]() { exitApp(app); });
		r.OnHover([&app]() { showMousePos(app); });
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
			std::string path = "Images\\wand." + std::string((rem == 0) ? "jpg" : "png");
			wand::Sprite& s = app.GetEntityManager()->AddSprite(path);
			s.GetTransform()->SetPos(x, y);
			s.GetTransform()->SetDepth(0);
			s.GetTransform()->SetWidth(100);
			s.GetTransform()->SetHeight(100);
		}
	}
	
	// Render semi-transparent text
	wand::TextBox& t1 = app.GetEntityManager()->AddTextBox("arial", 20, textColor);
	t1.GetTransform()->SetPos(0, 0);
	t1.GetTransform()->SetDepth(5);
	t1.GetTransform()->SetWidth(window->GetWidth());
	t1.GetTransform()->SetHeight(window->GetHeight());
	std::string text = "";
	for (int i = 0; i < 1; i++)
	{
		text += "The quick brown fox jumps over the lazy dog. ";
	}
	t1.SetText(text);
}
