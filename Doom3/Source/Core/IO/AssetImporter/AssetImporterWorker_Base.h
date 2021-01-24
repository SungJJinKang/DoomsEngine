#pragma once
#include <optional>

#include "../../Core.h"

#include "../../Asset/Asset.h"
#include "../../../Helper/ThreadPool_Cpp/ThreadPool.h"


namespace Doom
{
	namespace AssetImporter
	{
		template <Asset::AssetType assetType>
		inline std::optional<Asset::asset_type_t<assetType>> ReadAssetFile(std::filesystem::path path);
	}
}