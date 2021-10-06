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

doom::GameCore::~GameCore()
{

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
	D_START_PROFILING("mJobSystem Init", eProfileLayers::CPU);
	mJobSystem.Init();
	D_END_PROFILING("mJobSystem Init");


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

void doom::GameCore::Update()
{
	UpdateGameCore();

	D_START_PROFILING("mTime_Server.Update_Internal", eProfileLayers::CPU);
	mTime_Server.Update_Internal();
	mTime_Server.Update();
	D_END_PROFILING("mTime_Server.Update_Internal");

	D_START_PROFILING("mPhysics_Server.Update", eProfileLayers::CPU);
	mPhysics_Server.Update_Internal();
	mPhysics_Server.Update();
	D_END_PROFILING("mPhysics_Server.Update");

	D_START_PROFILING("mUserImput_Server.Update", eProfileLayers::CPU);
	mUserImput_Server.Update_Internal();
	mUserImput_Server.Update();
	D_END_PROFILING("mUserImput_Server.Update");

	D_START_PROFILING("mCurrentScene->UpdatePlainComponents", eProfileLayers::CPU);
	mCurrentScene->UpdatePlainComponents(); // Update plain Components ( Game Logic )
	D_END_PROFILING("mCurrentScene->UpdatePlainComponents");

	D_START_PROFILING("mGraphics_Server.Update", eProfileLayers::CPU);
	mGraphics_Server.Update_Internal();
	mGraphics_Server.Update();
	D_END_PROFILING("mGraphics_Server.Update");
}

void doom::GameCore::FixedUpdate()
{
	D_START_PROFILING("mPhysics_Server.FixedUpdate_Internal", eProfileLayers::CPU);
	mPhysics_Server.FixedUpdate_Internal();
	D_END_PROFILING("mPhysics_Server.FixedUpdate_Internal");

	D_START_PROFILING("mPhysics_Server.FixedUpdate", eProfileLayers::CPU);
	mPhysics_Server.FixedUpdate();
	D_END_PROFILING("mPhysics_Server.FixedUpdate");

	D_START_PROFILING("mCurrentScene->FixedUpdatePlainComponents", eProfileLayers::CPU);
	mCurrentScene->FixedUpdatePlainComponents(); // Update plain Components ( Game Logic )
	D_END_PROFILING("mCurrentScene->FixedUpdatePlainComponents");
}

void doom::GameCore::OnEndOfFrame()
{
	D_START_PROFILING("mTime_Server OnEndOfFrame", eProfileLayers::CPU);
	mTime_Server.OnEndOfFrame_Internal();
	mTime_Server.OnEndOfFrame();
	D_END_PROFILING("mTime_Server OnEndOfFrame");

	D_START_PROFILING("mPhysics_Server OnEndOfFrame", eProfileLayers::CPU);
	mPhysics_Server.OnEndOfFrame_Internal();
	mPhysics_Server.OnEndOfFrame();
	D_END_PROFILING("mPhysics_Server OnEndOfFrame");

	D_START_PROFILING("mUserImput_Server OnEndOfFrame", eProfileLayers::CPU);
	mUserImput_Server.OnEndOfFrame_Internal();
	mUserImput_Server.OnEndOfFrame();
	D_END_PROFILING("mUserImput_Server OnEndOfFrame");

	D_START_PROFILING("mCurrentScene OnEndOfFrame", eProfileLayers::CPU);
	mCurrentScene->OnEndOfFrameOfEntities(); // Update Plain Components ( Game Logic )
	D_END_PROFILING("mCurrentScene OnEndOfFrame");

	D_START_PROFILING("mGraphics_Server OnEndOfFrame", eProfileLayers::CPU);
	mGraphics_Server.OnEndOfFrame_Internal();
	mGraphics_Server.OnEndOfFrame();
	D_END_PROFILING("mGraphics_Server OnEndOfFrame");
}

bool doom::GameCore::Tick()
{

	D_START_PROFILING("Fixed Update", eProfileLayers::CPU);
	MainTimer::ResetFixedTimer();
	int fixedUpdateCount{ 0 };
	for (int i = 0; i < MAX_PHYSICS_STEP; ++i)
	{
		fixedUpdateCount++;
		FixedUpdate();
		MainTimer::UpdateFixedTimer();
		if (MainTimer::GetFixedDeltaTime() > FIXED_TIME_STEP)
		{
			break;
		}
	}
	D_END_PROFILING("Fixed Update");


	MainTimer::UpdateFrameTimer();

	D_START_PROFILING("Update", eProfileLayers::CPU);
	Update();
	D_END_PROFILING("Update");


	D_START_PROFILING("OnEndOfFrame", eProfileLayers::CPU);
	OnEndOfFrame();
	D_END_PROFILING("OnEndOfFrame");

	if (doom::userinput::UserInput_Server::GetKeyUp(doom::userinput::eKEY_CODE::KEY_ESCAPE) == false)
	{
		return true;
	}
	else
	{
		return false;
	}

	
}

void doom::GameCore::CleanUp()
{

}
