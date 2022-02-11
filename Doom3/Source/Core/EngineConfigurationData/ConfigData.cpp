#include "ConfigData.h"

dooms::ConfigData::ConfigData()
	: mConfigFilePath(nullptr), mConfigData()
{
	D_START_PROFILING(Loading_Config_File, eProfileLayers::CPU);
	mConfigData = { SimpleIniParser::ParseIniFile(dooms::path::_GetAssetFolderDirectory() + "config.ini") };
	D_END_PROFILING(Loading_Config_File);
}

IniData& dooms::ConfigData::GetConfigData()
{
	return mConfigData;
}
