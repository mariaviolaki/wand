#include "WandPCH.h"
#include "Random.h"

namespace wand
{
	Random::Random()
	{
		// Use the random device to seed the generator once
		std::random_device rd;
		mRNG = std::mt19937(rd());
	}

	int Random::GetInt(int first, int last)
	{
		std::uniform_int_distribution<int> dist(first, last);
		return dist(mRNG);
	}

	float Random::GetFloat(float first, float last)
	{
		std::uniform_real_distribution<float> dist(first, last);
		return dist(mRNG);
	}
}