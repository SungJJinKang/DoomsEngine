#include "GameCore.h"

#include "../Graphics/Graphics.h"

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
	this->mGraphics.Init();
	D_END_PROFILING("Init GLFW");


	D_START_PROFILING("ImportEntireAsset", doom::profiler::eProfileLayers::CPU);
	this->mAssetManager.ImportEntireAsset();
	D_END_PROFILING("ImportEntireAsset");

	this->mThreadManager.InitializeThreads();

}

void doom::GameCore::Update()
{
	this->mGraphics.Update();
}

