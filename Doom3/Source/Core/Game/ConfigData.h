#pragma once
#include <Core.h>
#include "SimpleIniParser.h"

namespace dooms
{
	class GameCore;
	class DOOM_API D_CLASS ConfigData : public DObject, public ISingleton<ConfigData>
	{
		

		//TODO : Remove friend class
		friend class GameCore;

	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		

	public:
		
		ConfigData()
		{
			D_START_PROFILING(Loading_Config_File, eProfileLayers::CPU);
			mConfigData = { SimpleIniParser::ParseIniFile(dooms::path::_GetAssetFolderDirectory() + "config.ini") };
			D_END_PROFILING(Loading_Config_File);
		}

		IniData& GetConfigData()
		{
			return mConfigData;
		}
	};
}