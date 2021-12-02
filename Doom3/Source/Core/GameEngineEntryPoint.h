#pragma once

#include "Core.h"
#include "Game/GameCore.h"

#include <DObject/DObjectManager.h>
#include <OS/ErrorHandling.h>

//void ExitGame();


#include <iostream>
#include <cstdio>

namespace dooms
{
	int GameEngineEntryPoint()
	{
		{
			{
				dooms::errorHandling::SetUnHandledExceptionHandling();

				dooms::GameCore gameCore{};

				D_START_PROFILING(Init_Game, dooms::profiler::eProfileLayers::CPU);
				gameCore.Init();
				D_END_PROFILING(Init_Game);

				while (gameCore.Tick())
				{
				}
				gameCore.CleanUp();
				//window terminated
			}


#ifdef DEBUG_MODE
			dooms::DObjectManager::DestroyAllDObjects(false); // for detecting memory leak
#endif

		}


		std::cout << "\nLast DObject Count : " << dooms::DObjectManager::GetDObjectCount() << std::endl;
		std::fflush(stdout);

		return 0;
	}

}



