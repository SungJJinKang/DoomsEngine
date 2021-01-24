#include "Random.h"


std::random_device doom::Random::rd{};
std::mt19937 doom::Random::rng{ doom::Random::rd() };



void doom::Random::GenerateSeed()
{
	doom::Random::rng.seed(rd());
}

int doom::Random::RandomIntNumber(int a, int b)
{
	std::uniform_int_distribution<int> dist(a, b);
	return dist(doom::Random::rng);
}

float doom::Random::RandomFloatNumber(float a, float b)
{
	std::uniform_real_distribution<float> dist(a, b); 
	return dist(doom::Random::rng);
}






