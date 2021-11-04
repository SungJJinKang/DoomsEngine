#pragma once
#include <random>

#include <Core.h>

namespace doom
{
	namespace random
	{
		class D_CLASS Random
		{
		private:
			static std::mt19937 rng;
			static std::random_device rd;
		public:

			D_FUNCTION()
			static void GenerateSeed();

			D_FUNCTION()
			static INT32 RandomIntNumber(INT32 a, INT32 b);

			D_FUNCTION()
			static FLOAT32 RandomFloatNumber(FLOAT32 a, FLOAT32 b);
		};
		
	}
	
}

using namespace doom::random;

