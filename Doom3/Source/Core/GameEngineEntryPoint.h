#pragma once

#include "Core.h"
#include "Game/GameCore.h"

#include <DObject/DObjectManager.h>
#include <OS/ErrorHandling.h>

//void ExitGame();


#include <iostream>
#include <cstdio>

namespace doom
{
	int GameEngineEntryPoint()
	{
		{
			{
				doom::errorHandling::SetUnHandledExceptionHandling();

				doom::GameCore gameCore{};

				D_START_PROFILING(Init_Game, doom::profiler::eProfileLayers::CPU);
				gameCore.Init();
				D_END_PROFILING(Init_Game);

				while (gameCore.Tick())
				{
				}
				gameCore.CleanUp();
				//window terminated
			}


#ifdef DEBUG_MODE
			doom::DObjectManager::DestroyAllDObjects(false);
#endif

		}


		std::cout << "\nLast DObject Count : " << doom::DObjectManager::GetDObjectCount() << std::endl;
		std::fflush(stdout);

		return 0;
	}

}



