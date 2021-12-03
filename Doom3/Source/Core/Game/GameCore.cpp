#include "GameCore.h"

#include "../Graphics/Graphics_Server.h"

#include <utility/SimpleIniParser.h>
#include "AssetManager/AssetManager.h"

#include "../../GameLogic/GameLogicStartPoint.h"
#include "ConfigData.h"
#include "MainTimer.h"
#include <GarbageCollector/GarbageCollectorManager.h>

#include "../Logger/logger.h"


dooms::GameCore::GameCore()
{


}




std::unique_ptr<dooms::Scene> dooms::GameCore::CreateNewScene(std::string sceneName /*= ""*/)
{
	return std::unique_ptr<dooms::Scene>{dooms::CreateDObject<Scene>(sceneName)};
}

void dooms::GameCore::InitGameSetting()
{
	ITERATION_PER_SECOND = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "ITERATION_PER_SECOND");
	TARGET_FRAME_RATE = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "TARGET_FRAME_RATE");
	FRAME_DELAY_MILLISECOND = mGameConfigData.GetConfigData().GetValue<INT32>("SYSTEM", "FRAME_DELAY_MILLISECOND");
	FIXED_TIME_STEP = static_cast<FLOAT32>(mGameConfigData.GetConfigData().GetValue<FLOAT64>("PHYSICS", "FIXED_TIME_STEP"));
	MAX_PHYSICS_STEP = mGameConfigData.GetConfigData().GetValue<INT32>("PHYSICS", "MAX_PHYSICS_STEP");

	


#ifdef DEBUG_MODE
	dooms::logger::InitLogger();
#endif

}

void dooms::GameCore::UpdateGameCore()
{

}

dooms::GameCore::~GameCore()
{
	mCurrentScene->DestroyAllEntity();
}

void dooms::GameCore::Init()
{
	D_START_PROFILING(InitGameSetting, eProfileLayers::CPU);
	InitGameSetting();
	D_END_PROFILING(InitGameSetting);
	
	InitServers();
	LateInit();

	mCurrentScene = CreateNewScene();

	GameLogicStartPoint::StartGameLogic();



	gc::GarbageCollectorManager::Collect();
}

void dooms::GameCore::InitServers()
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

	D_START_PROFILING(Init_ReflectionManager, eProfileLayers::CPU);
	mReflectionManager.Initialize();
	D_END_PROFILING(Init_ReflectionManager);


	D_START_PROFILING(Init_mGarbageCollectorManager, eProfileLayers::CPU);
	dooms::gc::GarbageCollectorManager::Init();
	D_END_PROFILING(Init_mGarbageCollectorManager);

}

void dooms::GameCore::LateInit()
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
	
}

void dooms::GameCore::Update()
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

	D_START_PROFILING(mGarbageCollectorManager_Update, eProfileLayers::CPU);
	dooms::gc::GarbageCollectorManager::TickGC();
	D_END_PROFILING(mGarbageCollectorManager_Update);
}

void dooms::GameCore::FixedUpdate()
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

void dooms::GameCore::OnEndOfFrame()
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

bool dooms::GameCore::Tick()
{

	D_START_PROFILING(Fixed_Update, eProfileLayers::CPU);
	MainTimer::GetSingleton()->ResetFixedTimer();
	INT32 fixedUpdateCount{ 0 };
	for (INT32 i = 0; i < MAX_PHYSICS_STEP; ++i)
	{
		fixedUpdateCount++;
		FixedUpdate();
		MainTimer::GetSingleton()->UpdateFixedTimer();
		if (MainTimer::GetSingleton()->GetFixedDeltaTime() > FIXED_TIME_STEP)
		{
			break;
		}
	}
	D_END_PROFILING(Fixed_Update);


	MainTimer::GetSingleton()->UpdateFrameTimer();

	D_START_PROFILING(Update, eProfileLayers::CPU);
	Update();
	D_END_PROFILING(Update);


	D_START_PROFILING(OnEndOfFrame, eProfileLayers::CPU);
	OnEndOfFrame();
	D_END_PROFILING(OnEndOfFrame);

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::userinput::eKEY_CODE::KEY_ESCAPE) == false)
	{
		return true;
	}
	else
	{
		return false;
	}

	
}

void dooms::GameCore::CleanUp()
{

}
