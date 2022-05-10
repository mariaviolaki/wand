#pragma once

#include "Utils/Pair.h"

namespace wand
{
	class State
	{
	public:
		State(const std::string& name);

		std::string GetName() const;
		// Get all the pairs saved in this state
		const std::vector<std::shared_ptr<Pair>>& GetStateData() const;

		// Add a key-value pair to the state
		void Add(Pair* pair);
		// Append a vector of pairs to the already existing ones
		void Add(std::vector<std::shared_ptr<Pair>> stateData);
		void Add(std::vector<std::shared_ptr<Pair>>&& stateData);

	private:
		std::string mName;
		std::vector<std::shared_ptr<Pair>> mStateData;
	};
}
