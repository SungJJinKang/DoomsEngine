#include "GameCore.h"

#include "../Graphics/GraphicsAPI.h"
#include "../Graphics/GraphicsManager.h"

#include "../../Helper/SimpleIniParser.h"
#include "AssetManager.h"




IniData& doom::GameCore::GetConfigData()
{
	return this->mConfigData;
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

}

void doom::GameCore::Update()
{
	
	D_START_PROFILING("GraphicsUpdate", eProfileLayers::GPU);
	this->mGraphicsManager.Update();
	D_END_PROFILING("GraphicsUpdate");

	this->OnEndOfFrame();
}

void doom::GameCore::OnEndOfFrame()
{
	this->mGraphicsManager.OnEndOfFrame();

	this->mCurrentScene->OnEndOfFrameOfEntities();
}
