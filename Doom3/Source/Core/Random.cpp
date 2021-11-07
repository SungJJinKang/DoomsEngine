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

		FLOAT32 dooms::random::Random::RandomFloatNumber(FLOAT32 a, FLOAT32 b)
		{
			std::uniform_real_distribution<FLOAT32> dist(a, b);
			return dist(Random::rng);
		}
	}
}





