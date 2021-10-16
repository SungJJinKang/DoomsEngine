#include "GameCore.h"

#include "../Graphics/Graphics_Server.h"

#include <utility/SimpleIniParser.h>
#include "AssetManager/AssetManager.h"

#include "../../GameLogic/GameLogicStartPoint.h"
#include "ConfigData.h"
#include "MainTimer.h"

#include "../Logger/Logger.h"


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
	ITERATION_PER_SECOND = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "ITERATION_PER_SECOND");
	TARGET_FRAME_RATE = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "TARGET_FRAME_RATE");
	FRAME_DELAY_MILLISECOND = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "FRAME_DELAY_MILLISECOND");
	FIXED_TIME_STEP = static_cast<FLOAT32>(mGameConfigData.GetConfigData().GetValue<FLOAT64>("PHYSICS", "FIXED_TIME_STEP"));
	MAX_PHYSICS_STEP = mGameConfigData.GetConfigData().GetValue<INT32>("PHYSICS", "MAX_PHYSICS_STEP");

	


#ifdef DEBUG_MODE
	doom::logger::Logger::InitLogger();
#endif

}

void doom::GameCore::UpdateGameCore()
{

}

doom::GameCore::~GameCore()
{

}

void doom::GameCore::Init()
{
	D_START_PROFILING(InitGameSetting, eProfileLayers::CPU);
	InitGameSetting();
	D_END_PROFILING(InitGameSetting);


	InitServers();





	LateInit();
}

void doom::GameCore::InitServers()
{
	D_START_PROFILING(mJobSystem_Init, eProfileLayers::CPU);
	mJobSystem.Init();
	D_END_PROFILING(mJobSystem_Init);


	D_START_PROFILING(mTime_Server_Init, eProfileLayers::CPU);
	mTime_Server.Init();
	D_END_PROFILING(mTime_Server_Init);

	//
	//Read This : https://docs.unity3d.com/Manual/class-TimeManager.html
	D_START_PROFILING(Init_Physics_Server, eProfileLayers::CPU);
	mPhysics_Server.Init();
	D_END_PROFILING(Init_Physics_Server);

	D_START_PROFILING(Init_Graphics_Server, eProfileLayers::Rendering);
	mGraphics_Server.Init();
	D_END_PROFILING(Init_Graphics_Server);

	D_START_PROFILING(Init_UserInput_Server, eProfileLayers::CPU);
	mUserImput_Server.Init();
	D_END_PROFILING(Init_UserInput_Server);

	D_START_PROFILING(Init_AssetManager, eProfileLayers::CPU);
	mAssetManager.Init();
	D_END_PROFILING(Init_AssetManager);
}

void doom::GameCore::LateInit()
{
	/*
	D_START_PROFILING(Init Physics_Server, eProfileLayers::CPU);
	mPhysics_Server.Init();
	D_END_PROFILING(Init Physics_Server);
	*/

	D_START_PROFILING(LateInit_Graphics_Server, eProfileLayers::Rendering);
	mGraphics_Server.LateInit();
	D_END_PROFILING(LateInit_Graphics_Server);

	/*
	D_START_PROFILING(Init UserInput_Server, eProfileLayers::CPU);
	mUserImput_Server.Init();
	D_END_PROFILING(Init UserInput_Server);
	*/
	GameLogicStartPoint::StartGameLogic();
}

void doom::GameCore::Update()
{
	UpdateGameCore();

	D_START_PROFILING(mJobSystem_Update, eProfileLayers::CPU);
	mJobSystem.Update_Internal();
	mJobSystem.Update();
	D_END_PROFILING(mJobSystem_Update);

	D_START_PROFILING(mTime_Server_Update, eProfileLayers::CPU);
	mTime_Server.Update_Internal();
	mTime_Server.Update();
	D_END_PROFILING(mTime_Server_Update);

	D_START_PROFILING(mPhysics_Server_Update, eProfileLayers::CPU);
	mPhysics_Server.Update_Internal();
	mPhysics_Server.Update();
	D_END_PROFILING(mPhysics_Server_Update);

	D_START_PROFILING(mUserImput_Server_Update, eProfileLayers::CPU);
	mUserImput_Server.Update_Internal();
	mUserImput_Server.Update();
	D_END_PROFILING(mUserImput_Server_Update);

	D_START_PROFILING(mCurrentScene_UpdatePlainComponents, eProfileLayers::CPU);
	mCurrentScene->UpdatePlainComponents(); // Update plain Components ( Game Logic )
	D_END_PROFILING(mCurrentScene_UpdatePlainComponents);

	D_START_PROFILING(mGraphics_Server_Update, eProfileLayers::CPU);
	mGraphics_Server.Update_Internal();
	mGraphics_Server.Update();
	D_END_PROFILING(mGraphics_Server_Update);
}

void doom::GameCore::FixedUpdate()
{
	D_START_PROFILING(mPhysics_Server_FixedUpdate_Internal, eProfileLayers::CPU);
	mPhysics_Server.FixedUpdate_Internal();
	D_END_PROFILING(mPhysics_Server_FixedUpdate_Internal);

	D_START_PROFILING(mPhysics_Server_FixedUpdate, eProfileLayers::CPU);
	mPhysics_Server.FixedUpdate();
	D_END_PROFILING(mPhysics_Server_FixedUpdate);

	D_START_PROFILING(mCurrentScene_FixedUpdatePlainComponents, eProfileLayers::CPU);
	mCurrentScene->FixedUpdatePlainComponents(); // Update plain Components ( Game Logic )
	D_END_PROFILING(mCurrentScene_FixedUpdatePlainComponents);
}

void doom::GameCore::OnEndOfFrame()
{
	D_START_PROFILING(mTime_Server_OnEndOfFrame, eProfileLayers::CPU);
	mTime_Server.OnEndOfFrame_Internal();
	mTime_Server.OnEndOfFrame();
	D_END_PROFILING(mTime_Server_OnEndOfFrame);

	D_START_PROFILING(mPhysics_Server_OnEndOfFrame, eProfileLayers::CPU);
	mPhysics_Server.OnEndOfFrame_Internal();
	mPhysics_Server.OnEndOfFrame();
	D_END_PROFILING(mPhysics_Server_OnEndOfFrame);

	D_START_PROFILING(mUserImput_Server_OnEndOfFrame, eProfileLayers::CPU);
	mUserImput_Server.OnEndOfFrame_Internal();
	mUserImput_Server.OnEndOfFrame();
	D_END_PROFILING(mUserImput_Server_OnEndOfFrame);

	D_START_PROFILING(mCurrentScene_OnEndOfFrame, eProfileLayers::CPU);
	mCurrentScene->OnEndOfFrameOfEntities(); // Update Plain Components ( Game Logic )
	D_END_PROFILING(mCurrentScene_OnEndOfFrame);

	D_START_PROFILING(mGraphics_Server_OnEndOfFrame, eProfileLayers::CPU);
	mGraphics_Server.OnEndOfFrame_Internal();
	mGraphics_Server.OnEndOfFrame();
	D_END_PROFILING(mGraphics_Server_OnEndOfFrame);
}

bool doom::GameCore::Tick()
{

	D_START_PROFILING(Fixed_Update, eProfileLayers::CPU);
	MainTimer::ResetFixedTimer();
	INT32 fixedUpdateCount{ 0 };
	for (INT32 i = 0; i < MAX_PHYSICS_STEP; ++i)
	{
		fixedUpdateCount++;
		FixedUpdate();
		MainTimer::UpdateFixedTimer();
		if (MainTimer::GetFixedDeltaTime() > FIXED_TIME_STEP)
		{
			break;
		}
	}
	D_END_PROFILING(Fixed_Update);


	MainTimer::UpdateFrameTimer();

	D_START_PROFILING(Update, eProfileLayers::CPU);
	Update();
	D_END_PROFILING(Update);


	D_START_PROFILING(OnEndOfFrame, eProfileLayers::CPU);
	OnEndOfFrame();
	D_END_PROFILING(OnEndOfFrame);

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
