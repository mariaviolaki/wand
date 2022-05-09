#pragma once

namespace wand
{
	class Random
	{
	public:
		static void Init();
		static int GetInt(int first, int last);
		static float GetFloat(float first, float last);

	private:
		static std::mt19937 sRNG;

		Random();
	};
}