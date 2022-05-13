#pragma once

#include "State.h"
#include "Core/FileManager.h"

namespace wand
{
	class StateManager
	{
	public:
		StateManager();

		void Init(FileManager* fileManager);
		// Save a given state to memory and write it to a file
		void SaveState(std::shared_ptr<State> state, const std::string& filename);
		// Overwrite the states in memory with the ones loaded from a file
		void LoadStates(const std::string& filename);
		// Use a state name to get an already loaded state
		State* GetState(const std::string& stateName);

	private:
		std::unordered_map<std::string, std::shared_ptr<State>> mStates;
		FileManager* mFileManager;
	};
}
