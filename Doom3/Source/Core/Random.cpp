#include "Random.h"

namespace dooms
{
	namespace random
	{
		std::random_device Random::rd{};
		std::mt19937 Random::rng{ Random::rd() };

		void dooms::random::Random::GenerateSeed()
		{
			Random::rng.seed(Random::rd());
		}

		INT32 dooms::random::Random::RandomIntNumber(INT32 a, INT32 b)
		{
			std::uniform_int_distribution<INT32> dist(a, b);
			return dist(Random::rng);
		}

		INT32 dooms::random::Random::RandomIntNumber()
		{
			std::uniform_int_distribution<INT32> dist(INT_MIN, INT32_MAX);
			return dist(Random::rng);
		}

		UINT32 Random::RandomUIntNumber(UINT32 a, UINT32 b)
		{
			std::uniform_int_distribution<UINT32> dist(a, b);
			return dist(Random::rng);
		}

		UINT32 Random::RandomUIntNumber()
		{
			std::uniform_int_distribution<UINT32> dist(UINT32_MIN, UINT32_MAX);
			return dist(Random::rng);
		}

		FLOAT32 dooms::random::Random::RandomFloatNumber(FLOAT32 a, FLOAT32 b)
		{
			std::uniform_real_distribution<FLOAT32> dist(a, b);
			return dist(Random::rng);
		}
	}
}





