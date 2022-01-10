#include "GraphicsAPI.h"

#include <cassert>

double dooms::graphics::GraphicsAPI::GetTime()
{
	assert(0);
	return 0;
}

unsigned int dooms::graphics::GraphicsAPI::Initialize(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
{
	assert(0);
	return 1;
}

unsigned int dooms::graphics::GraphicsAPI::DeInitialize()
{
	assert(0);
	return 1;
}

void dooms::graphics::GraphicsAPI::SwapBuffer() noexcept
{
	assert(0);
}
