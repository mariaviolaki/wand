#include "WandPCH.h"
#include "App.h"

namespace wand
{
	App::App()
		: mWindow(std::make_shared<Window>()), mCursorManager(std::make_shared<CursorManager>()),
		mInput(std::make_shared<Input>()), mRenderer(std::make_shared<Renderer>()),
		mEntityManager(std::make_shared<EntityManager>()), mEventManager(std::make_shared<EventManager>()),
		mStateManager(std::make_shared<StateManager>()), mInputManager(std::make_shared<InputManager>()),
		mFontManager(std::make_shared<FontManager>()), mAudioManager(std::make_shared<AudioManager>()),
		mFileManager(std::make_shared<FileManager>()), mRandom(std::make_shared<Random>())
	{
		mWindow->Init([this](Event* event)
		{
			this->OnEvent(event);
		});
		mCursorManager->Init(mWindow->GetGLFWWindow());
		mRenderer->Init(mWindow->GetWidth(), mWindow->GetHeight(), mFileManager->GetShaderPath());
		mEntityManager->Init(mFontManager.get());
		mEventManager->Init(mWindow.get(), mInput.get(), mRenderer.get(), mCursorManager.get());
		mInputManager->Init(mWindow->GetGLFWWindow());
		mStateManager->Init(mFileManager.get());
	}

	App::~App()
	{}

	void App::Clear() const
	{
		// Clear past events
		mEventManager->Clear();
		// Clear old graphics and poll events
		mWindow->Clear();
	}

	void App::Update() const
	{
		// Set the active entities to be processed in this frame
		mEventManager->SetEntities(mEntityManager->GetEntities());
		// Render all graphics visible in this frame
		mRenderer->Submit(mEntityManager->GetEntities());
		// Update the graphics in the window
		mWindow->Update();
	}

	bool App::IsRunning() const { return !mWindow->IsClosed(); }

	void App::Exit() const { mWindow->Close(); }

	void App::OnEvent(Event* event)
	{
		mEventManager->HandleEvent(event);
	}

	Input* App::GetInput() const { return mInput.get(); }
	Window* App::GetWindow() const { return mWindow.get(); }
	Random* App::GetRandom() const { return mRandom.get(); }
	CursorManager* App::GetCursorManager() const { return mCursorManager.get(); }
	EntityManager* App::GetEntityManager() const { return mEntityManager.get(); }
	StateManager* App::GetStateManager() const { return mStateManager.get(); }
	FontManager* App::GetFontManager() const { return mFontManager.get(); }
	AudioManager* App::GetAudioManager() const { return mAudioManager.get(); }
	FileManager* App::GetFileManager() const { return mFileManager.get(); }
}
