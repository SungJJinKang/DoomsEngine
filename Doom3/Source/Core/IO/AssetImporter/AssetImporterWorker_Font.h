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
		inline std::optional <Asset::asset_type_t<Asset::eAssetType::FONT>> ReadAssetFile<Asset::eAssetType::FONT>(std::filesystem::path path)
		{
			return {};
		}

	}
}