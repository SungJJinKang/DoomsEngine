#include "GameFlow.h"

#include "../Grahpics/Graphics.h"

void Doom::GameFlow::Init()
{
	Graphics::Init();
}

bool Doom::GameFlow::Loop()
{
	Graphics::Loop();
	return true;
}

