#include "WandPCH.h"
#include "App.h"
#include "Utils/Random.h"
#include "Utils/Logger.h"

namespace wand
{
	App::App(std::string name, unsigned int width, unsigned int height)
		: mWindow(std::make_shared<Window>(name, width, height)),
		mCursorManager(std::make_shared<CursorManager>()), mInput(std::make_shared<Input>()),
		mRenderer(std::make_shared<Renderer>()), mEntityManager(std::make_shared<EntityManager>()),
		mEventManager(std::make_shared<EventManager>()), mStateManager(std::make_shared<StateManager>()),
		mInputManager(std::make_shared<InputManager>()), mFontManager(std::make_shared<FontManager>()),
		mAudioManager(std::make_shared<AudioManager>()), mFileManager(std::make_shared<FileManager>())
	{
		// Initialize all subsystems
		Logger::Init(mFileManager->GetRootFolder());
		Random::Init();

		mWindow->Init
		(
			[this](Event* event) { this->OnEvent(event); },
			[this]() { this->Update(); }
		);
		mCursorManager->Init(mWindow->GetGLFWWindow());
		mRenderer->Init(mWindow->GetWidth(), mWindow->GetHeight(), mFileManager->GetShaderPath());
		mEntityManager->Init(mFontManager.get());
		mEventManager->Init(mWindow.get(), mInput.get(), mRenderer.get(), mCursorManager.get());
		mStateManager->Init(mFileManager.get());
		mInputManager->Init(mWindow->GetGLFWWindow());
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
	CursorManager* App::GetCursorManager() const { return mCursorManager.get(); }
	EntityManager* App::GetEntityManager() const { return mEntityManager.get(); }
	StateManager* App::GetStateManager() const { return mStateManager.get(); }
	FontManager* App::GetFontManager() const { return mFontManager.get(); }
	AudioManager* App::GetAudioManager() const { return mAudioManager.get(); }
	FileManager* App::GetFileManager() const { return mFileManager.get(); }
}
