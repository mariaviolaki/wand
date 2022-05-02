#pragma once

#include "Window.h"
#include "CursorManager.h"
#include "Input/Input.h"
#include "Graphics/Renderer.h"
#include "UI/UIEntity.h"
#include "EntityManager.h"
#include "Input/InputManager.h"
#include "Events/EventManager.h"
#include "State/StateManager.h"
#include "Graphics/FontManager.h"
#include "Audio/AudioManager.h"
#include "FileManager.h"
#include "Utils/Random.h"

namespace wand
{
	class App
	{
	public:
		App();
		~App();

		void Clear() const;
		void Update() const;
		bool IsRunning() const;
		void Exit() const;

		void OnEvent(Event* event);

		Input* GetInput() const;
		Window* GetWindow() const;
		Random* GetRandom() const;
		CursorManager* GetCursorManager() const;
		EntityManager* GetEntityManager() const;
		StateManager* GetStateManager() const;
		FontManager* GetFontManager() const;
		AudioManager* GetAudioManager() const;
		FileManager* GetFileManager() const;
		
	private:
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<CursorManager> mCursorManager;
		std::unique_ptr<Input> mInput;
		std::unique_ptr<Renderer> mRenderer;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<InputManager> mInputManager;
		std::unique_ptr<EventManager> mEventManager;
		std::unique_ptr<StateManager> mStateManager;
		std::unique_ptr<FontManager> mFontManager;
		std::unique_ptr<AudioManager> mAudioManager;
		std::unique_ptr<FileManager> mFileManager;
		std::unique_ptr<Random> mRandom;
	};
}
