#include "Random.h"

namespace doom
{
	namespace random
	{
		std::random_device Random::rd{};
		std::mt19937 Random::rng{ Random::rd() };

		void doom::random::Random::GenerateSeed()
		{
			Random::rng.seed(Random::rd());
		}

		INT32 doom::random::Random::RandomIntNumber(INT32 a, INT32 b)
		{
			std::uniform_int_distribution<INT32> dist(a, b);
			return dist(Random::rng);
		}

		FLOAT32 doom::random::Random::RandomFloatNumber(FLOAT32 a, FLOAT32 b)
		{
			std::uniform_real_distribution<FLOAT32> dist(a, b);
			return dist(Random::rng);
		}
	}
}





