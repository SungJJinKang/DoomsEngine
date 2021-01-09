#pragma once

#include <string>
#include <filesystem>

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
		std::string AssetName;
		std::filesystem::path AssetPath;
	};
}


