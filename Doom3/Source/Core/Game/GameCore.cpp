#include "GameCore.h"

#include "../Graphics/Graphics_Server.h"

#include <Misc/IniFile/SimpleIniParser.h>
#include <Asset/AssetManager/AssetManager.h>

#include "../../GameLogic/GameLogicStartPoint.h"
#include "MainTimer.h"
#include <GarbageCollector/GarbageCollectorManager.h>

#include "../Logger/logger.h"
#include <Graphics/GraphicsAPI/Input/GraphicsAPIInput.h>

#define DEFAULT_MAX_PHYSICS_STEP 8

dooms::GameCore::GameCore()
	:
	ITERATION_PER_SECOND(),
	TARGET_FRAME_RATE(),
	FRAME_DELAY_MILLISECOND(),
	FIXED_TIME_STEP(),
	MAX_PHYSICS_STEP(DEFAULT_MAX_PHYSICS_STEP),
	mSceneManager(),
	mAssetManager(),
	mGraphics_Server(),
	mPhysics_Server(),
	mJobSystem(),
	mUserImput_Server(),
	mTime_Server(),
	mReflectionManager(),
	mMemoryManager(),
	mGameConfigData()
{


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

void dooms::GameCore::InitializeGraphicsAPI(const int argc, char* const* const argv)
{
	graphics::GraphicsAPI::eGraphicsAPIType targetGraphicsAPI = graphics::GraphicsAPI::eGraphicsAPIType::GraphicsAPIType_NONE;

	for(size_t i = 0 ; i < argc ; i++)
	{
		if(_stricmp(argv[i], "OPENGL") == 0)
		{
			targetGraphicsAPI = graphics::GraphicsAPI::eGraphicsAPIType::OpenGL;
		}
		else if
		( 
			(_stricmp(argv[i], "DX11") == 0) || 
			(_stricmp(argv[i], "DX11_10") == 0) || 
			(_stricmp(argv[i], "DIRECTX") == 0) ||
			(_stricmp(argv[i], "DIRECTX11") == 0) ||
			(_stricmp(argv[i], "DIRECTX11_10") == 0)
		)
		{
			targetGraphicsAPI = graphics::GraphicsAPI::eGraphicsAPIType::DX11_10;
		}
	}

	D_START_PROFILING(LoadGraphisAPI, eProfileLayers::CPU);
	mGraphics_Server.InitializeGraphicsAPI(targetGraphicsAPI);
	D_END_PROFILING(LoadGraphisAPI);

}

dooms::GameCore::~GameCore()
{

}

void dooms::GameCore::Init(const int argc, char* const* const argv)
{
	D_START_PROFILING(InitGameSetting, eProfileLayers::CPU);
	InitGameSetting();
	D_END_PROFILING(InitGameSetting);
	
	InitServers(argc, argv);
	LateInit();

	GameLogicStartPoint::StartGameLogic();



	gc::GarbageCollectorManager::Collect(gc::garbageCollectorSolver::eGCMethod::MultiThreadMark, true);
	dooms::gc::GarbageCollectorManager::ResetElapsedTime();
}

void dooms::GameCore::InitServers(const int argc, char* const* const argv)
{
	mMemoryManager.Init(argc, argv);

	D_START_PROFILING(Init_ReflectionManager, eProfileLayers::CPU);
	mReflectionManager.Initialize();
	D_END_PROFILING(Init_ReflectionManager);

	InitializeGraphicsAPI(argc, argv);

	D_START_PROFILING(mJobSystem_Init, eProfileLayers::CPU);
	mJobSystem.Init(argc, argv);
	D_END_PROFILING(mJobSystem_Init);

	D_START_PROFILING(Init_AssetManager, eProfileLayers::CPU);
	mAssetManager.Init(argc, argv);
	D_END_PROFILING(Init_AssetManager);

	D_START_PROFILING(mTime_Server_Init, eProfileLayers::CPU);
	mTime_Server.Init(argc, argv);
	D_END_PROFILING(mTime_Server_Init);

	//
	//Read This : https://docs.unity3d.com/Manual/class-TimeManager.html
	D_START_PROFILING(Init_Physics_Server, eProfileLayers::CPU);
	mPhysics_Server.Init(argc, argv);
	D_END_PROFILING(Init_Physics_Server);

	D_START_PROFILING(Init_Graphics_Server, eProfileLayers::Rendering);
	mGraphics_Server.Init(argc, argv);
	D_END_PROFILING(Init_Graphics_Server);

	D_START_PROFILING(Init_UserInput_Server, eProfileLayers::CPU);
	mUserImput_Server.Init(argc, argv);
	D_END_PROFILING(Init_UserInput_Server);

	mSceneManager.Init(argc, argv);
	


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

	mSceneManager.LateInit();

}

void dooms::GameCore::Update()
{
	UpdateGameCore();

	D_START_PROFILING(mUserImput_Server_Update, eProfileLayers::CPU);
	mUserImput_Server.Update_Internal();
	mUserImput_Server.UpdateInput();
	D_END_PROFILING(mUserImput_Server_Update);

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

	D_START_PROFILING(mSceneManager_Update, eProfileLayers::CPU);
	mSceneManager.Update(); // Update plain Components ( Game Logic )
	D_END_PROFILING(mSceneManager_Update);

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

	D_START_PROFILING(mSceneManager_FixedUpdate, eProfileLayers::CPU);
	mSceneManager.FixedUpdate();
	D_END_PROFILING(mSceneManager_FixedUpdate);
}

void dooms::GameCore::OnEndOfFrame()
{
	D_START_PROFILING(mUserImput_Server_OnEndOfFrame, eProfileLayers::CPU);
	mUserImput_Server.OnEndOfFrame_Internal();
	mUserImput_Server.OnEndOfFrame();
	D_END_PROFILING(mUserImput_Server_OnEndOfFrame);


	D_START_PROFILING(mJobSystem_Update, eProfileLayers::CPU);
	mJobSystem.OnEndOfFrame_Internal();
	mJobSystem.OnEndOfFrame();
	D_END_PROFILING(mJobSystem_Update);

	D_START_PROFILING(mTime_Server_OnEndOfFrame, eProfileLayers::CPU);
	mTime_Server.OnEndOfFrame_Internal();
	mTime_Server.OnEndOfFrame();
	D_END_PROFILING(mTime_Server_OnEndOfFrame);

	D_START_PROFILING(mPhysics_Server_OnEndOfFrame, eProfileLayers::CPU);
	mPhysics_Server.OnEndOfFrame_Internal();
	mPhysics_Server.OnEndOfFrame();
	D_END_PROFILING(mPhysics_Server_OnEndOfFrame);



	D_START_PROFILING(mSceneManager_OnEndOfFrame, eProfileLayers::CPU);
	mSceneManager.OnEndOfFrame(); // Update Plain Components ( Game Logic )
	D_END_PROFILING(mSceneManager_OnEndOfFrame);

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

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE) == false)
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
