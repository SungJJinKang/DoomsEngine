#include "GameCore.h"
#include "../../Helper/IniParser.h"
#include "GameFlow.h"
const char* Doom::GameCore::configFilePath{};
IniData Doom::GameCore::ConfigData{};

void Doom::GameCore::Init()
{
	Doom::GameCore::ConfigData = { IniParser::ParseIniFile(GET_RALATIVE_PATH("config.ini")) };
	GameFlow::Init();
}

bool Doom::GameCore::Loop()
{
	return GameFlow::Loop();
}

