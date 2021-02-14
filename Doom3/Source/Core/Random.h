#pragma once
#include <random>


namespace doom
{
	namespace random
	{
		class Random
		{
		private:
			static std::mt19937 rng;
			static std::random_device rd;
		public:
			static void GenerateSeed();
			static int RandomIntNumber(int a, int b);
			static float RandomFloatNumber(float a, float b);
		};
		
	}
	
}

using namespace doom::random;

