#pragma once

#include <filesystem>
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextAsset.h"


namespace doom
{
	namespace assetimporter
	{
		template<>
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXT>> ImportSpecificAsset<Asset::eAssetType::TEXT>(const std::filesystem::path& path);
	}
}