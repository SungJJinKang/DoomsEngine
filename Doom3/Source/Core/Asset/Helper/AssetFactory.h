#pragma once

#include <Core.h>

#include "../Asset.h"
#include <filesystem>

namespace doom
{
	namespace asset
	{
		namespace AssetFactory
		{
			doom::asset::Asset* CreateNewAsset(const doom::asset::eAssetType eAssetType);
			doom::asset::Asset* CreateNewAsset(const std::filesystem::path& path, const doom::asset::eAssetType eAssetType);
		}
	}
}

