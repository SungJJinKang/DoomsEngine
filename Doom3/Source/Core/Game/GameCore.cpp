#include "GameCore.h"

#include "GameFlow.h"
#include "../Graphics/Graphics.h"

#include "../../Helper/IniParser.h"
#include "AssetManager.h"


const char* doom::GameCore::configFilePath{};
IniData doom::GameCore::ConfigData{};

void doom::GameCore::Init()
{
	D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
	doom::GameCore::ConfigData = { IniParser::ParseIniFile(GET_RELATIVE_PATH("config.ini")) };
	D_END_PROFILING("Loading Config File");

	D_START_PROFILING("Init GLFW", eProfileLayers::GPU);
	doom::graphics::Graphics::Init();
	D_END_PROFILING("Init GLFW");

	D_START_PROFILING("ImportEntireAsset", doom::profiler::eProfileLayers::CPU);
	AssetManager::ImportEntireAsset();
	D_END_PROFILING("ImportEntireAsset");

	GameFlow::Init();
}


