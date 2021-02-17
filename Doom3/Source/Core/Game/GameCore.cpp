#include "GameCore.h"

#include "../Graphics/GraphicsAPI.h"
#include "../Graphics/Graphics_Server.h"

#include "../../Helper/SimpleIniParser.h"
#include "AssetManager.h"

#include "../../GameLogic/TEST.h"




doom::GameCore::GameCore()
{
	this->mCurrentScene = this->CreateNewScene();
}

IniData& doom::GameCore::GetConfigData()
{
	return this->mConfigData;
}


std::unique_ptr<doom::Scene> doom::GameCore::CreateNewScene(std::string sceneName /*= ""*/)
{
	return std::unique_ptr<doom::Scene>{new Scene(sceneName)};
}

void doom::GameCore::Init()
{
	this->mTime_Server.Init();

	D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
	this->mConfigData = { SimpleIniParser::ParseIniFile(ASSET_FOLDER_DIRECTORY + "config.ini") };
	D_END_PROFILING("Loading Config File");



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

	this->mThreadManager.InitializeThreads();

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


