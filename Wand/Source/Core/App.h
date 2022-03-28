#pragma once

#include "Window.h"
#include "State.h"
#include "EntityManager.h"
#include "Graphics/Renderer.h"
#include "UI/UIComponent.h"
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

		AudioManager* GetAudioManager() const;
		UIComponent& AddEntity(UIComponent* entity) const;
		// Save a given state to memory and write it to a file
		void SaveState(std::shared_ptr<State> state, const std::string& filename);
		// Overwrite the states in memory with the ones loaded from a file
		void LoadStates(const std::string& filename);
		
	private:
		std::unique_ptr<Window> mWindow;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<Renderer> mRenderer;
		std::unique_ptr<AudioManager> mAudioManager;
		std::unordered_map<std::string, std::shared_ptr<State>> mStates;
	};
}
