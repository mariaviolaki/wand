#include "WandPCH.h"
#include "App.h"

#include "Input/Input.h"
#include "Graphics/FontManager.h"
#include "UI/UIManager.h"

namespace wand
{
	App::App()
		: mWindow(std::make_unique<Window>()), mEntityManager(std::make_unique<EntityManager>()),
		mRenderer(std::make_unique<Renderer>())
	{
		Start();
	}

	App::~App()
	{
		// Delete the fonts stored during runtime
		FontManager::Clear();
	}

	void App::Update() const
	{
		// Update the graphics in the window and process events
		mWindow->Update();
		// Process the OnClick functions of the UI components
		UIManager::ProcessClickFunction();
		// Render all graphics visible in this frame
		mRenderer->Submit(mEntityManager->GetEntities());
	}

	bool App::IsRunning() const { return !mWindow->IsClosed(); }

	UIComponent& App::AddEntity(UIComponent* entity)
	{ 
		mEntityManager->Add(entity);
		return *entity;
	}

	void App::Start()
	{
		Input::SetupCallbacks(mWindow->GetGLFWWindow());
	}
}
