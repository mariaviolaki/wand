#include "WandPCH.h"
#include "Random.h"

namespace wand
{
	std::mt19937 Random::sRNG = std::mt19937();

	void Random::Init()
	{
		// Use the random device to seed the generator once
		std::random_device rd;
		sRNG = std::mt19937(rd());
	}

	int Random::GetInt(int first, int last)
	{
		std::uniform_int_distribution<int> dist(first, last);
		return dist(sRNG);
	}

	float Random::GetFloat(float first, float last)
	{
		std::uniform_real_distribution<float> dist(first, last);
		return dist(sRNG);
	}
}