#include "GameCore.h"
#include "../../Helper/IniParser.h"
#include "GameFlow.h"

#include "AssetManager.h"

const char* Doom::GameCore::configFilePath{};
IniData Doom::GameCore::ConfigData{};

void Doom::GameCore::Init()
{
	Doom::GameCore::ConfigData = { IniParser::ParseIniFile(GET_RELATIVE_PATH("config.ini")) };


	AssetManager::ImportEntireAsset();


	GameFlow::Init();
}


