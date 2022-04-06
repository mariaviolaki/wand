#pragma once

#include "Window.h"
#include "State.h"
#include "UI/UIEntity.h"
#include "EntityManager.h"
#include "Input/Input.h"
#include "Input/InputManager.h"
#include "Events/EventManager.h"
#include "Graphics/Renderer.h"
#include "Audio/AudioManager.h"

namespace wand
{
	class App
	{
	public:
		App();
		~App();

		void Update() const;
		bool IsRunning() const;

		void OnEvent(Event* event);

		AudioManager* GetAudioManager() const;
		UIEntity& AddEntity(UIEntity* entity) const;
		// Save a given state to memory and write it to a file
		void SaveState(std::shared_ptr<State> state, const std::string& filename);
		// Overwrite the states in memory with the ones loaded from a file
		void LoadStates(const std::string& filename);
		
	private:
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<EventManager> mEventManager;
		std::unique_ptr<Input> mInput;
		std::unique_ptr<InputManager> mInputManager;
		std::unique_ptr<AudioManager> mAudioManager;
		std::unique_ptr<Renderer> mRenderer;
		std::unordered_map<std::string, std::shared_ptr<State>> mStates;
	};
}
