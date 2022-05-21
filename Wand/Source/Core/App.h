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

namespace wand
{
	class App
	{
	public:
		App(std::string name = "Wand Game", unsigned int width = 960, unsigned int height = 540);
		~App();

		void Clear() const;
		void Update() const;
		bool IsRunning() const;
		void Exit() const;

		void OnEvent(Event* event);

		Input* GetInput() const;
		Window* GetWindow() const;
		CursorManager* GetCursorManager() const;
		EntityManager* GetEntityManager() const;
		StateManager* GetStateManager() const;
		FontManager* GetFontManager() const;
		AudioManager* GetAudioManager() const;
		FileManager* GetFileManager() const;

	private:
		// Use shared pointers for each subsystem so that app can be copied
		std::shared_ptr<Window> mWindow;
		std::shared_ptr<CursorManager> mCursorManager;
		std::shared_ptr<Input> mInput;
		std::shared_ptr<Renderer> mRenderer;
		std::shared_ptr<EntityManager> mEntityManager;
		std::shared_ptr<InputManager> mInputManager;
		std::shared_ptr<EventManager> mEventManager;
		std::shared_ptr<StateManager> mStateManager;
		std::shared_ptr<FontManager> mFontManager;
		std::shared_ptr<AudioManager> mAudioManager;
		std::shared_ptr<FileManager> mFileManager;
	};
}
