#include "GameCore.h"

#include "../Graphics/GraphicsAPI.h"
#include "../Graphics/Graphics_Server.h"

#include "../../Helper/SimpleIniParser.h"
#include "AssetManager.h"

#include "../../GameLogic/TEST.h"
#include "ConfigData.h"




doom::GameCore::GameCore()
{
	this->mCurrentScene = this->CreateNewScene();
}




std::unique_ptr<doom::Scene> doom::GameCore::CreateNewScene(std::string sceneName /*= ""*/)
{
	return std::unique_ptr<doom::Scene>{new Scene(sceneName)};
}

void doom::GameCore::InitGameSetting()
{
	this->ITERATION_PER_SECOND = this->mMainConfigData.GetConfigData().GetValue<int>("SYSTEM", "ITERATION_PER_SECOND");
	this->TARGET_FRAME_RATE = this->mMainConfigData.GetConfigData().GetValue<int>("SYSTEM", "TARGET_FRAME_RATE");
	this->FRAME_DELAY_MILLISECOND = this->mMainConfigData.GetConfigData().GetValue<int>("SYSTEM", "FRAME_DELAY_MILLISECOND");

	this->mPhysics_Server.FIXED_TIME_STEP = static_cast<float>(this->mMainConfigData.GetConfigData().GetValue<double>("PHYSICS", "FIXED_TIME_STEP"));
	this->mPhysics_Server.MAX_PHYSICS_STEP = this->mMainConfigData.GetConfigData().GetValue<int>("PHYSICS", "MAX_PHYSICS_STEP");


}

void doom::GameCore::Init()
{
	this->InitGameSetting();


	this->mTime_Server.Init();
	this->mThreadManager.Init();

	



	//
	//Read This : https://docs.unity3d.com/Manual/class-TimeManager.html
	D_START_PROFILING("Init Physics_Server", eProfileLayers::CPU);
	this->mPhysics_Server.Init();
	D_END_PROFILING("Init Physics_Server");

	D_START_PROFILING("Init Graphics_Server", eProfileLayers::GPU);
	this->mGraphics_Server.Init();
	D_END_PROFILING("Init Graphics_Server");

	D_START_PROFILING("Init UserInput_Server", eProfileLayers::CPU);
	this->mUserImput_Server.Init();
	D_END_PROFILING("Init UserInput_Server");



	D_START_PROFILING("ImportEntireAsset", doom::profiler::eProfileLayers::CPU);
	this->mAssetManager.ImportEntireAsset();
	D_END_PROFILING("ImportEntireAsset");



	this->LateInit();
}

void doom::GameCore::LateInit()
{
	/*
	D_START_PROFILING("Init Physics_Server", eProfileLayers::CPU);
	this->mPhysics_Server.Init();
	D_END_PROFILING("Init Physics_Server");
	*/

	D_START_PROFILING("LateInit Graphics_Server", eProfileLayers::GPU);
	this->mGraphics_Server.LateInit();
	D_END_PROFILING("LateInit Graphics_Server");

	/*
	D_START_PROFILING("Init UserInput_Server", eProfileLayers::CPU);
	this->mUserImput_Server.Init();
	D_END_PROFILING("Init UserInput_Server");
	*/
	TEST::Init();
}

void doom::GameCore::CleanUp()
{

}
