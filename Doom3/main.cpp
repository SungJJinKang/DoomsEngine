#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"

#include <DObject/DObjectManager.h>

void ExitGame();


#include <iostream>
#include <cstdio>


int main()
{
	DObjectManager mDObjectManager;

	GameCore gameCore{};

	D_START_PROFILING("Init Game", doom::profiler::eProfileLayers::CPU);
	gameCore.Init();
	D_END_PROFILING("Init Game");

	while (gameCore.Tick())
	{
	}
	gameCore.CleanUp();
	//window terminated

	std::cout << std::endl;
	std::fflush(stdout);
}




void ExitGame()
{

}