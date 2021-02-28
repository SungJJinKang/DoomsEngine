#pragma once
#include "../Core.h"
#include "SimpleIniParser.h"

namespace doom
{
	class GameCore;
	class ConfigData : public ISingleton<ConfigData>
	{
		friend class GameCore;

	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		ConfigData()
		{
			D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
			this->mConfigData = { SimpleIniParser::ParseIniFile(ASSET_FOLDER_DIRECTORY + "config.ini") };
			D_END_PROFILING("Loading Config File");
		}

	public:
		

		const IniData& GetConfigData() const
		{
			return this->mConfigData;
		}
	};
}