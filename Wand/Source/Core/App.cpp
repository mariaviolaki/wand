#include "WandPCH.h"
#include "App.h"
#include "Graphics/FontManager.h"
#include "Utils/Serializer.h"
#include "UI/Text.h"

namespace wand
{
	App::App()
		: mWindow(std::make_unique<Window>()), mFontManager(std::make_unique<FontManager>()),
		mEntityManager(std::make_unique<EntityManager>()), mEventManager(std::make_unique<EventManager>()),
		mInput(std::make_unique<Input>()), mInputManager(std::make_unique<InputManager>()),
		mAudioManager(std::make_unique<AudioManager>()), mRenderer(std::make_unique<Renderer>())
	{
		mWindow->Init([this](Event* event)
		{
			this->OnEvent(event);
		});
		mEntityManager->Init(mFontManager.get());
		mEventManager->Init(mWindow.get(), mInput.get(), mRenderer.get());
		mInputManager->Init(mWindow->GetGLFWWindow());
		mRenderer->Init(mWindow->GetWidth(), mWindow->GetHeight());
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

	void App::OnEvent(Event* event)
	{
		mEventManager->HandleEvent(event);
	}

	Input& App::GetInput() const { return *mInput.get(); }
	Window& App::GetWindow() const { return *mWindow.get(); }
	EntityManager* App::GetEntityManager() const { return mEntityManager.get(); }
	FontManager* App::GetFontManager() const { return mFontManager.get(); }
	AudioManager* App::GetAudioManager() const { return mAudioManager.get(); }

	void App::SaveState(std::shared_ptr<State> state, const std::string& filename)
	{
		std::string stateName = state->GetName();
		// Save new state only if its name doesn't already exist
		if (mStates.find(stateName) == mStates.end())
		{
			mStates.insert(std::make_pair(state->GetName(), state));
			// Save the data in a file in JSON format
			std::string path = std::filesystem::current_path().string() + "\\Saves\\" + filename;
			Serializer serializer;
			serializer.Serialize(*state.get(), path);
			return;
		}
		std::cout << "App: State '" << stateName << "' already exists.\n";
	}

	void App::LoadStates(const std::string& filename)
	{
		// Deserialize the states stored in a file and store them in an unordered map
		std::string path = std::filesystem::current_path().string() + "\\Saves\\" + filename;
		Serializer serializer;
		auto newStates = serializer.Deserialize(path);
		// If the map is not empty, overwrite the states
		if (!newStates.empty())
		{
			mStates.clear();
			mStates = newStates;
		}
	}
}
