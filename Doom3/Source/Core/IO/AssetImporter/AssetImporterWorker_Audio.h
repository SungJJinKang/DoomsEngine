#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/AudioAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		inline std::optional<Asset::asset_type_t<Asset::eAssetType::AUDIO>> ImportSpecificAsset<Asset::eAssetType::AUDIO>(const std::filesystem::path& path)
		{
			return {};
		}

	}
}