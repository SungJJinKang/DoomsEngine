#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextureAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXTURE>> ImportSpecificAsset<Asset::eAssetType::TEXTURE>(const std::filesystem::path& path);
	}
}