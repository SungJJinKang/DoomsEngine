#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/AudioAsset.h"

namespace Doom
{
	namespace AssetImporter
	{
		template <>
		inline std::optional<Asset::asset_type_t<Asset::AssetType::AUDIO>> ReadAssetFile<Asset::AssetType::AUDIO>(std::filesystem::path path)
		{
			return {};
		}

	}
}