#pragma once
#include "AssetImporterWorker.h"
#include "../../Asset/AudioAsset.h"

namespace Doom
{
	namespace AssetImporter
	{
		template <>
		std::optional<Asset::asset_type_t<Asset::AssetType::AUDIO>> ReadAssetFile<Asset::AssetType::AUDIO>(std::filesystem::path path)
		{
			return {};
		}

	}
}