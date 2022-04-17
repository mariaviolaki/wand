#pragma once

#include "State/State.h"
#include "nlohmann/json.hpp"

namespace wand
{
	class Serializer
	{
	public:
		void Serialize(const State& state, const std::string& path);
		std::unordered_map<std::string, std::shared_ptr<State>> Deserialize(const std::string& path);

	private:
		// Helper methods for serialization
		nlohmann::json CreateStateList(const nlohmann::json& oldStates, const State& newState);
		nlohmann::json CreatePairs(const State& state);
		nlohmann::json CreateValue(const Pair& pair);
		// Helper methods for deserialization
		nlohmann::json GetSavedStates(const std::string& path);
		std::shared_ptr<State> GetState(std::string name, const nlohmann::json& state);
		Pair* GetPair(std::string name, const nlohmann::json& value);
	};
}
