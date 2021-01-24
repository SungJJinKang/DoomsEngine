#include "GameCore.h"
#include "../../Helper/IniParser.h"
#include "GameFlow.h"

#include "AssetManager.h"

const char* doom::GameCore::configFilePath{};
IniData doom::GameCore::ConfigData{};

void doom::GameCore::Init()
{
	doom::GameCore::ConfigData = { IniParser::ParseIniFile(GET_RELATIVE_PATH("config.ini")) };


	AssetManager::ImportEntireAsset();


	GameFlow::Init();
}


