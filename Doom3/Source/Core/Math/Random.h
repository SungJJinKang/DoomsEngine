#pragma once
#include <random>

#include <Core.h>

namespace dooms
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
			static void GenerateSeed(const UINT32 seed);
			static INT32 RandomIntNumber(INT32 a, INT32 b);
			static INT32 RandomIntNumber();
			static UINT32 RandomUIntNumber(UINT32 a, UINT32 b);
			static UINT32 RandomUIntNumber();
			static FLOAT32 RandomFloatNumber(FLOAT32 a, FLOAT32 b);
		};
		
	}
	
}

using namespace dooms::random;

