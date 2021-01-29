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
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXTURE>> ReadAssetFile<Asset::eAssetType::TEXTURE>(std::filesystem::path path);
	}
}