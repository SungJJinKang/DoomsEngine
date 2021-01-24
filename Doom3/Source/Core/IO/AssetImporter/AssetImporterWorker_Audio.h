#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/AudioAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		inline std::optional<Asset::asset_type_t<Asset::eAssetType::AUDIO>> ReadAssetFile<Asset::eAssetType::AUDIO>(std::filesystem::path path)
		{
			return {};
		}

	}
}