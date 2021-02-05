#include "GameCore.h"

#include "GameFlow.h"
#include "../Graphics/Graphics.h"

#include "../../Helper/SimpleIniParser.h"
#include "AssetManager.h"
#include "../Thread/ThreadManager.h"


const char* doom::GameCore::configFilePath{};
IniData doom::GameCore::ConfigData{};

void doom::GameCore::Init()
{
	D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
	doom::GameCore::ConfigData = { SimpleIniParser::ParseIniFile(GET_RELATIVE_PATH("config.ini")) };
	D_END_PROFILING("Loading Config File");

	D_START_PROFILING("Init GLFW", eProfileLayers::GPU);
	doom::graphics::Graphics::Init();
	D_END_PROFILING("Init GLFW");

	D_START_PROFILING("ImportEntireAsset", doom::profiler::eProfileLayers::CPU);
	AssetManager::ImportEntireAsset();
	D_END_PROFILING("ImportEntireAsset");

	doom::thread::ThreadManager::InitializeThreads();

	GameFlow::Init();
}


