#pragma once
#include <Core.h>
#include "SimpleIniParser.h"

namespace doom
{
	class GameCore;
	class ConfigData : public DObject, public ISingleton<ConfigData>
	{
		DOBJECT_CLASS_BODY(ConfigData, doom::eDOBJECT_ClassFlags::NonCopyable);

		//TODO : Remove friend class
		friend class GameCore;

	private:
		const char* mConfigFilePath{};
		IniData mConfigData{};

		

	public:
		
		ConfigData()
		{
			D_START_PROFILING(Loading_Config_File, eProfileLayers::CPU);
			mConfigData = { SimpleIniParser::ParseIniFile(doom::path::_GetAssetFolderDirectory() + "config.ini") };
			D_END_PROFILING(Loading_Config_File);
		}

		IniData& GetConfigData()
		{
			return mConfigData;
		}
	};
}