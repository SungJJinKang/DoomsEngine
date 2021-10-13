#include "Source/Core/Core.h"
#include "Source/Core/Game/GameCore.h"

#include <DObject/DObjectManager.h>

void ExitGame();


#include <iostream>
#include <cstdio>


int main()
{
	{
		doom::GameCore gameCore{};

		D_START_PROFILING(Init_Game, doom::profiler::eProfileLayers::CPU);
		gameCore.Init();
		D_END_PROFILING(Init_Game);

		while (gameCore.Tick())
		{
		}
		gameCore.CleanUp();
		//window terminated

#ifdef DEBUG_MODE
		DObjectManager::DestroyAllDObjects(false);
#endif
		
	}


	std::cout << "\nLast DObject Count : " << doom::DObjectManager::GetDObjectCount() << std::endl;
	std::fflush(stdout);
}




void ExitGame()
{

}