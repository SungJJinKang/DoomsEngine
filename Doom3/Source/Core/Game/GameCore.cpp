#include "GameCore.h"

#include "../Graphics/GraphicsAPI.h"
#include "../Graphics/GraphicsManager.h"

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
	D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
	this->mConfigData = { SimpleIniParser::ParseIniFile(GET_RELATIVE_PATH("config.ini")) };
	D_END_PROFILING("Loading Config File");


	D_START_PROFILING("Init GLFW", eProfileLayers::GPU);
	this->mGraphicsManager.Init();
	D_END_PROFILING("Init GLFW");


	D_START_PROFILING("ImportEntireAsset", doom::profiler::eProfileLayers::CPU);
	this->mAssetManager.ImportEntireAsset();
	D_END_PROFILING("ImportEntireAsset");

	this->mThreadManager.InitializeThreads();

	TEST::Init();
}


