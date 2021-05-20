#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"

void ExitGame();


#include <iostream>



int main()
{
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
}




void ExitGame()
{

}