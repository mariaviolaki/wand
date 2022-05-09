#pragma once

#include "State/State.h"
#include "nlohmann/json.hpp"

namespace wand
{
	class Serializer
	{
	public:
		static void Serialize(const State& state, const std::string& path);
		static std::unordered_map<std::string, std::shared_ptr<State>> Deserialize(const std::string& path);

	private:
		Serializer();

		// Helper methods for serialization
		static nlohmann::json CreateStateList(const nlohmann::json& oldStates, const State& newState);
		static nlohmann::json CreatePairs(const State& state);
		static nlohmann::json CreateValue(const Pair& pair);
		// Helper methods for deserialization
		static nlohmann::json GetSavedStates(const std::string& path);
		static std::shared_ptr<State> GetState(std::string name, const nlohmann::json& state);
		static Pair* GetPair(std::string name, const nlohmann::json& value);
	};
}
