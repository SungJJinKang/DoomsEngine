#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"
#include "Source/Core/Game/GameFlow.h"


using namespace doom;

void ExitGame();


#include <iostream>

int main()
{
	D_START_PROFILING("Start Game", doom::profiler::eProfileLayers::CPU);
	D_END_PROFILING("Start Game");

	GameCore::Init();


	GameFlow::Loop();

	//window terminated

	std::cout << std::endl;
}




void ExitGame()
{

}