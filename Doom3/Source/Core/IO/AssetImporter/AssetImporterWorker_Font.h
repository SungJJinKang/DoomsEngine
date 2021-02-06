#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/FontAsset.h"

using namespace doom;

namespace doom
{
	namespace assetimporter
	{

		template <>
		inline std::optional <Asset::asset_type_t<Asset::eAssetType::FONT>> ImportSpecificAsset<Asset::eAssetType::FONT>(const std::filesystem::path& path)
		{
			return {};
		}

	}
}