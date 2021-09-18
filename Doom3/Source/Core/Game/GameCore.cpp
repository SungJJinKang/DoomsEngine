#include "GameCore.h"

#include "../Graphics/GraphicsAPI.h"
#include "../Graphics/Graphics_Server.h"

#include "../../Helper/SimpleIniParser.h"
#include "AssetManager/AssetManager.h"

#include "../../GameLogic/GameLogicStartPoint.h"
#include "ConfigData.h"

#include "AssetImporter/AssetImporterWorker_Texture.h"

#include "../Logger/Logger.h"
#include "../Profiler/Profiler.h"


doom::GameCore::GameCore()
{
	mCurrentScene = CreateNewScene();
}




std::unique_ptr<doom::Scene> doom::GameCore::CreateNewScene(std::string sceneName /*= ""*/)
{
	return std::unique_ptr<doom::Scene>{new Scene(sceneName)};
}

void doom::GameCore::InitGameSetting()
{
	ITERATION_PER_SECOND = mGameConfigData.GetConfigData().GetValue<int>("SYSTEM", "ITERATION_PER_SECOND");
	TARGET_FRAME_RATE = mGameConfigData.GetConfigData().GetValue<int>("SYSTEM", "TARGET_FRAME_RATE");
	FRAME_DELAY_MILLISECOND = mGameConfigData.GetConfigData().GetValue<int>("SYSTEM", "FRAME_DELAY_MILLISECOND");
	FIXED_TIME_STEP = static_cast<float>(mGameConfigData.GetConfigData().GetValue<double>("PHYSICS", "FIXED_TIME_STEP"));
	MAX_PHYSICS_STEP = mGameConfigData.GetConfigData().GetValue<int>("PHYSICS", "MAX_PHYSICS_STEP");

	


#ifdef DEBUG_MODE
	doom::logger::Logger::InitLogger();
	doom::profiler::Profiler::InitProfiling();
#endif

}

void doom::GameCore::UpdateGameCore()
{
#ifdef DEBUG_MODE
	if (userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_0))
	{
		doom::profiler::Profiler::SetActiveToggle();
	}
#endif

}

void doom::GameCore::Init()
{
	D_START_PROFILING("InitGameSetting", eProfileLayers::CPU);
	InitGameSetting();
	D_END_PROFILING("InitGameSetting");


	InitServers();





	LateInit();
}

void doom::GameCore::InitServers()
{

	D_START_PROFILING("mTime_Server Init", eProfileLayers::CPU);
	mTime_Server.Init();
	D_END_PROFILING("mTime_Server Init");

	//
	//Read This : https://docs.unity3d.com/Manual/class-TimeManager.html
	D_START_PROFILING("Init Physics_Server", eProfileLayers::CPU);
	mPhysics_Server.Init();
	D_END_PROFILING("Init Physics_Server");

	D_START_PROFILING("Init Graphics_Server", eProfileLayers::Rendering);
	mGraphics_Server.Init();
	D_END_PROFILING("Init Graphics_Server");

	D_START_PROFILING("Init UserInput_Server", eProfileLayers::CPU);
	mUserImput_Server.Init();
	D_END_PROFILING("Init UserInput_Server");

	D_START_PROFILING("Init AssetManager", eProfileLayers::CPU);
	mAssetManager.Init();
	D_END_PROFILING("Init AssetManager");
}

void doom::GameCore::LateInit()
{
	/*
	D_START_PROFILING("Init Physics_Server", eProfileLayers::CPU);
	mPhysics_Server.Init();
	D_END_PROFILING("Init Physics_Server");
	*/

	D_START_PROFILING("LateInit Graphics_Server", eProfileLayers::Rendering);
	mGraphics_Server.LateInit();
	D_END_PROFILING("LateInit Graphics_Server");

	/*
	D_START_PROFILING("Init UserInput_Server", eProfileLayers::CPU);
	mUserImput_Server.Init();
	D_END_PROFILING("Init UserInput_Server");
	*/
	GameLogicStartPoint::StartGameLogic();
}

void doom::GameCore::CleanUp()
{

}
