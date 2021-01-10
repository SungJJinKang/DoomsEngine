#pragma once

#include <string>
#include <filesystem>
#include "../API/UUID.h"

namespace Doom
{
	enum class AssetType
	{
		TEXTURE,
		THREE_D_MODELL,
		FONT,
		AUDIO
	};

	struct Asset
	{
		/// <summary>
		/// https://github.com/r-lyeh-archived/sole
		/// </summary>
		UUID uuid;
		std::string AssetName;
		std::filesystem::path AssetPath;

		void SetBaseMetaData(std::filesystem::path& path);

		Asset() : uuid{ GenerateUUID() }
		{

		}
	};
}


