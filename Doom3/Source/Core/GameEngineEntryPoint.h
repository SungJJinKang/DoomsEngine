#pragma once

#include "Core.h"
#include "Game/GameCore.h"

#include <DObject/DObjectManager.h>
#include <OS/ErrorHandling.h>
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "ResourceManagement/Thread/RunnableThread/GameThread.h"
#include <Misc/CommandLine.h>

//void ExitGame();


#include <iostream>
#include <cstdio>

namespace dooms
{
	int GameEngineEntryPoint(int argc, char* argv[])
	{
		{
			{
				dooms::errorHandling::SetUnHandledExceptionHandling();

				for(INT32 ArgumentIndex = 0 ; ArgumentIndex < argc ; ++ArgumentIndex)
				{
					CommandLine::AppendCommandLineString(argv[ArgumentIndex]);
				}

				dooms::GameCore gameCore{};

				D_START_PROFILING(Init_Game, dooms::profiler::eProfileLayers::CPU);
				gameCore.Init();
				D_END_PROFILING(Init_Game);

				dooms::thread::GameThread::GetSingleton()->SetTickFunction
				(
					[&gameCore]()
					{
						return gameCore.Tick();
					}
				);

				while (dooms::thread::GameThread::GetSingleton()->IsTerminated() == false)
				{
					dooms::thread::GameThread::GetSingleton()->Run_RunnableThread();
				}

				gameCore.CleanUp();
				//window terminated
			}

			dooms::DObjectManager::DestroyAllDObjects(false); // for detecting memory leak

		}

		dooms::graphics::GraphicsAPIManager::DeInitialize();

		D_ASSERT_LOG(dooms::DObjectManager::GetDObjectCount() == 0, "Never use DObject as static, global variable");
		std::cout << "Remained DObject Count : " << dooms::DObjectManager::GetDObjectCount() << std::endl;
		std::fflush(stdout);

		return 0;
	}

}



