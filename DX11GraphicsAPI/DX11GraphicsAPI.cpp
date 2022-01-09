#include "GraphicsAPI.h"

#include <cassert>

double dooms::graphics::GraphicsAPI::GetTime()
{
	assert(0);
	return 0;
}

unsigned int dooms::graphics::GraphicsAPI::Initialize()
{
	return 1;
}

unsigned int dooms::graphics::GraphicsAPI::DeInitialize()
{
	return 1;
}

void dooms::graphics::GraphicsAPI::SwapBuffer() noexcept
{

}
