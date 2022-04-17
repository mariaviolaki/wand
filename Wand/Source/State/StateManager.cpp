#include "WandPCH.h"
#include "StateManager.h"
#include "Utils/Serializer.h"

namespace wand
{
	StateManager::StateManager()
		: mFileManager(nullptr)
	{}

	void StateManager::Init(FileManager* fileManager) { mFileManager = fileManager; }

	void StateManager::SaveState(std::shared_ptr<State> state, const std::string& filename)
	{
		// Save new state by replacing the old one with the same name (if it exists)
		mStates.insert(std::make_pair(state->GetName(), state));
		// Save the data in a file in JSON format
		Serializer serializer;
		serializer.Serialize(*state.get(), mFileManager->GetSavePath() + filename);
	}

	void StateManager::LoadStates(const std::string& filename)
	{
		// Deserialize the states stored in a file and store them in an unordered map
		Serializer serializer;
		auto newStates = serializer.Deserialize(mFileManager->GetSavePath() + filename);
		// If the map is not empty, overwrite the states
		if (!newStates.empty())
		{
			mStates.clear();
			mStates = newStates;
		}
	}
}
