#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetImporterWorker.h"
#include "../../Asset/TextureAsset.h"

namespace Doom
{
	namespace AssetImporter
	{


		template <>
		std::optional <Asset::asset_type_t<Asset::AssetType::TEXTURE>> ReadAssetFile<Asset::AssetType::TEXTURE>(std::filesystem::path path)
		{
			return {};
		}
	}
}