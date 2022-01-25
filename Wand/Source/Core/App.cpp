#include "WandPCH.h"
#include "App.h"

#include "Input/Input.h"
#include "Graphics/Renderer.h"

namespace wand
{
	App::App()
		: mWindow(std::make_unique<Window>())
	{
		Start();
	}

	App::~App()
	{}

	int App::GetWidth() const
	{
		return mWindow.get()->GetWidth();
	}

	int App::GetHeight() const
	{
		return mWindow.get()->GetWidth();
	}

	bool App::IsRunning() const
	{
		return !mWindow.get()->IsClosed();
	}

	void App::Update() const
	{
		// Render all graphics submitted during this frame
		RenderManager::Render();
		// Update the graphics in the window and process events
		mWindow.get()->Update();
	}

	void App::Start()
	{
		InputManager::SetupCallbacks(mWindow.get()->GetGLFWWindow());
		RenderManager::Init(mWindow.get());
	}
}
