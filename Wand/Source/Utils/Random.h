#pragma once

namespace wand
{
	class Random
	{
	public:
		Random();

		int GetInt(int first, int last);
		float GetFloat(float first, float last);

	private:
		std::mt19937 mRNG;
	};
}