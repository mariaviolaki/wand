#include "WandPCH.h"
#include "Serializer.h"

namespace wand
{
	/******************************* PUBLIC METHODS **********************************/

	void Serializer::Serialize(const State& state, const std::string& path)
	{
		nlohmann::json states;
		nlohmann::json oldStates = GetSavedStates(path);

		// Add the new state to the old ones (if they exist)
		if (oldStates.is_null())
			states[state.GetName()] = CreatePairs(state);
		else
			states = CreateStateList(oldStates, state);

		// Write the data to a file in the given path (using 4 spaces for indentation)
		std::ofstream file(path);
		file << std::setw(4) << states << std::endl;
	}

	std::unordered_map<std::string, std::shared_ptr<State>> Serializer::Deserialize(const std::string& path)
	{
		std::unordered_map<std::string, std::shared_ptr<State>> states;
		nlohmann::json savedStates = GetSavedStates(path);

		// Create a new state using the JSON data for each state
		for (auto& state : savedStates.items())
		{
			states[state.key()] = GetState(state.key(), state.value());
		}
		return states;
	}

	/****************************** PRIVATE METHODS *********************************/

	nlohmann::json Serializer::CreateStateList(const nlohmann::json& oldStates, const State& newState)
	{
		nlohmann::json newStates;
		bool nameExists = false;

		// Access each state in the old list
		for (auto& state : oldStates.items())
		{
			// Copy its data to the new list
			newStates[state.key()] = state.value();
			// Check if the old state has the same name with the new one
			if (state.key() == newState.GetName())
				nameExists = true;
		}

		// Add the new state to the list if its name is unique
		if (nameExists)
			std::cout << "Serializer: State '" << newState.GetName() << "' already exists.\n";
		else
			newStates[newState.GetName()] = CreatePairs(newState);

		return newStates;
	}

	// Create a pair in JSON format for each name-value pair in the state
	nlohmann::json Serializer::CreatePairs(const wand::State& state)
	{
		nlohmann::json statePairs;
		for (const auto& pair : state.GetStateData())
		{
			statePairs[pair->GetName()] = CreateValue(*pair.get());
		}
		return statePairs;
	}

	// Store the data type and the actual value of a pair in single JSON object
	nlohmann::json Serializer::CreateValue(const Pair& pair)
	{
		nlohmann::json pairValue;
		// Save the appropriate value depending on its data type in the pair
		switch (pair.GetValueType())
		{
		case DataType::DT_INT:
			pairValue["type"] = "int";
			pairValue["value"] = pair.GetIntValue();
			break;
		case DataType::DT_DOUBLE:
			pairValue["type"] = "double";
			pairValue["value"] = pair.GetDoubleValue();
			break;
		case DataType::DT_BOOL:
			pairValue["type"] = "bool";
			pairValue["value"] = pair.GetBoolValue();
			break;
		case DataType::DT_STRING:
			pairValue["type"] = "string";
			pairValue["value"] = pair.GetStringValue();
			break;
		default:
			pairValue["type"] = "";
			pairValue["value"] = "";
		}

		return pairValue;
	}

	// Get the states from a file (in JSON format)
	nlohmann::json Serializer::GetSavedStates(const std::string& path)
	{
		nlohmann::json savedStates;
		// Copy the JSON data if the file exists
		std::ifstream file(path);
		if (file)
			file >> savedStates;
		
		return savedStates;
	}

	std::shared_ptr<State> Serializer::GetState(std::string name, const nlohmann::json& state)
	{
		std::shared_ptr<State> statePtr = std::make_shared<State>(name);
		// Add all the name-value pairs saved in the state
		for (auto& pair : state.items())
		{
			statePtr->Add(GetPair(pair.key(), pair.value()));
		}
		return statePtr;
	}

	Pair* Serializer::GetPair(std::string name, const nlohmann::json& value)
	{
		// Get the correct value based on the saved data type
		if (value["type"].get<std::string>() == "int")
			return new Pair(name, value["value"].get<int>());
		else if (value["type"].get<std::string>() == "double")
			return new Pair(name, value["value"].get<double>());
		else if (value["type"].get<std::string>() == "bool")
			return new Pair(name, value["value"].get<bool>());
		else
			return new Pair(name, value["value"].get<std::string>());
	}
}
