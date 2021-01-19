#pragma once
#include <random>


namespace Doom
{
	class Random
	{
		static std::mt19937 rng;
		static std::random_device rd;

		static void GenerateSeed();
		static int RandomIntNumber(int a, int b);
		static float RandomFloatNumber(float a, float b);
	};
}


