#include "WandPCH.h"
#include "App.h"

#include "Input/Input.h"
#include "Graphics/Renderer.h"
#include "Graphics/FontManager.h"

namespace wand
{
	App::App()
		: mWindow(std::make_unique<Window>())
	{
		Start();
	}

	App::~App()
	{
		// Delete the fonts stored during runtime
		FontManager::Clear();
	}

	bool App::IsRunning() const
	{
		return !mWindow->IsClosed();
	}

	void App::Update() const
	{
		// Render all graphics submitted during this frame
		Renderer::Render();
		// Update the graphics in the window and process events
		mWindow->Update();
	}

	void App::Start()
	{
		InputManager::SetupCallbacks(mWindow->GetGLFWWindow());
		Renderer::Init();
	}
}
