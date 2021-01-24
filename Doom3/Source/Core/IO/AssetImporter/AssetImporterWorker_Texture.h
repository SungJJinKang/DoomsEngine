#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextureAsset.h"

namespace Doom
{
	namespace AssetImporter
	{
		template <>
		inline std::optional <Asset::asset_type_t<Asset::AssetType::TEXTURE>> ReadAssetFile<Asset::AssetType::TEXTURE>(std::filesystem::path path)
		{
			return {};
		}
	}
}