#include "Random.h"

namespace doom
{
	namespace random
	{
		std::random_device Random::rd{};
		std::mt19937 Random::rng{ Random::rd() };

		void doom::random::GenerateSeed()
		{
			Random::rng.seed(Random::rd());
		}

		int doom::random::RandomIntNumber(int a, int b)
		{
			std::uniform_int_distribution<int> dist(a, b);
			return dist(Random::rng);
		}

		float doom::random::RandomFloatNumber(float a, float b)
		{
			std::uniform_real_distribution<float> dist(a, b);
			return dist(Random::rng);
		}
	}
}





