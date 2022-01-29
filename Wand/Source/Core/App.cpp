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
		return mWindow->GetWidth();
	}

	int App::GetHeight() const
	{
		return mWindow->GetWidth();
	}

	bool App::IsRunning() const
	{
		return !mWindow->IsClosed();
	}

	void App::Update() const
	{
		// Render all graphics submitted during this frame
		RenderManager::Render();
		// Update the graphics in the window and process events
		mWindow->Update();
	}

	void App::Start()
	{
		InputManager::SetupCallbacks(mWindow->GetGLFWWindow());
		RenderManager::Init(mWindow.get());
	}
}
