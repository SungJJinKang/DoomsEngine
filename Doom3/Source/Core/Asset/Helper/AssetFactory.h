#pragma once

#include <Core.h>

#include "../Asset.h"
#include <filesystem>

namespace dooms
{
	namespace asset
	{
		namespace AssetFactory
		{
			dooms::asset::Asset* CreateNewAsset(const dooms::asset::eAssetType eAssetType);
			dooms::asset::Asset* CreateNewAsset(const std::filesystem::path& path, const dooms::asset::eAssetType eAssetType);
		}
	}
}

