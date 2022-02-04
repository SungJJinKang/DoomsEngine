#pragma once
#include <random>

#include <Core.h>

namespace dooms
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
			static void GenerateSeed(const UINT32 seed);

			D_FUNCTION()
			static INT32 RandomIntNumber(INT32 a, INT32 b);

			D_FUNCTION()
			static INT32 RandomIntNumber();

			D_FUNCTION()
			static UINT32 RandomUIntNumber(UINT32 a, UINT32 b);

			D_FUNCTION()
			static UINT32 RandomUIntNumber();

			D_FUNCTION()
			static FLOAT32 RandomFloatNumber(FLOAT32 a, FLOAT32 b);
		};
		
	}
	
}

using namespace dooms::random;

