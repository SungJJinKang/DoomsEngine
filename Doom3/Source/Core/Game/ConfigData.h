#pragma once
#include "../Core.h"
#include "SimpleIniParser.h"

namespace doom
{
	class GameCore;
	class ConfigData : public DObject, public ISingleton<ConfigData>
	{
		friend class GameCore;

	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		ConfigData()
		{
			D_START_PROFILING("Loading Config File", eProfileLayers::CPU);
			mConfigData = { SimpleIniParser::ParseIniFile(doom::path::_GetAssetFolderDirectory() + "config.ini") };
			D_END_PROFILING("Loading Config File");
		}

	public:
		

		const IniData& GetConfigData() const
		{
			return mConfigData;
		}
	};
}