#pragma once
#include <random>

#include <Core.h>

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
			static INT32 RandomIntNumber(INT32 a, INT32 b);
			static FLOAT32 RandomFloatNumber(FLOAT32 a, FLOAT32 b);
		};
		
	}
	
}

using namespace doom::random;

