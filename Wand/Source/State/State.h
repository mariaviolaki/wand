#pragma once

#include "Utils/Pair.h"

namespace wand
{
	class State
	{
	public:
		State(const std::string& name);

		std::string GetName() const;
		const std::vector<std::shared_ptr<Pair>>& GetStateData() const;

		void Add(Pair* pair);
		void Add(std::vector<std::shared_ptr<Pair>> stateData);
		void Add(std::vector<std::shared_ptr<Pair>>&& stateData);

	private:
		std::string mName;
		std::vector<std::shared_ptr<Pair>> mStateData;
	};
}
