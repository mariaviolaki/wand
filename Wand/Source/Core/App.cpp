#include "WandPCH.h"
#include "App.h"

namespace wand
{
	App::App()
		: mWindow(std::make_unique<Window>()), mCursorManager(std::make_unique<CursorManager>()),
		mInput(std::make_unique<Input>()), mRenderer(std::make_unique<Renderer>()),
		mEntityManager(std::make_unique<EntityManager>()), mEventManager(std::make_unique<EventManager>()),
		mStateManager(std::make_unique<StateManager>()), mInputManager(std::make_unique<InputManager>()),
		mFontManager(std::make_unique<FontManager>()), mAudioManager(std::make_unique<AudioManager>()),
		mFileManager(std::make_unique<FileManager>()), mRandom(std::make_unique<Random>())
	{
		mWindow->Init([this](Event* event)
		{
			this->OnEvent(event);
		});
		mCursorManager->Init(mWindow->GetGLFWWindow());
		mRenderer->Init(mWindow->GetWidth(), mWindow->GetHeight());
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
