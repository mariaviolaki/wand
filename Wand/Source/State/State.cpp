#include "WandPCH.h"
#include "State.h"

namespace wand
{
	State::State(const std::string& name)
		: mName(name), mStateData()
	{}

	std::string State::GetName() const { return mName; }

	const std::vector<std::shared_ptr<Pair>>& State::GetStateData() const { return mStateData; }

	void State::Add(Pair* pair)
	{
		mStateData.push_back(std::shared_ptr<Pair>(pair));
	}

	void State::Add(std::vector<std::shared_ptr<Pair>> stateData)
	{
		mStateData.insert(mStateData.end(), stateData.begin(), stateData.end());
	}

	void State::Add(std::vector<std::shared_ptr<Pair>>&& stateData)
	{
		mStateData.insert(mStateData.end(), stateData.begin(), stateData.end());
	}
}
