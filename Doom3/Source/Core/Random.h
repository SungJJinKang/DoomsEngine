#pragma once
#include <random>


namespace doom
{
	namespace random
	{
		class Random
		{
		public:
			static std::mt19937 rng;
			static std::random_device rd;


		};
		void GenerateSeed();
		int RandomIntNumber(int a, int b);
		float RandomFloatNumber(float a, float b);
	}
	
}


