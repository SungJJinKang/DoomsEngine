#include "Random.h"


std::random_device Doom::Random::rd{};
std::mt19937 Doom::Random::rng{ Doom::Random::rd() };



void Doom::Random::GenerateSeed()
{
	Doom::Random::rng.seed(rd());
}

int Doom::Random::RandomIntNumber(int a, int b)
{
	std::uniform_int_distribution<int> dist(a, b);
	return dist(Doom::Random::rng);
}

float Doom::Random::RandomFloatNumber(float a, float b)
{
	std::uniform_real_distribution<float> dist(a, b); 
	return dist(Doom::Random::rng);
}






