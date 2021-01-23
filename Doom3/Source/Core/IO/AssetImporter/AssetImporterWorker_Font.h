#pragma once
#include "AssetImporterWorker.h"
#include "../../Asset/FontAsset.h"

using namespace Doom;

namespace Doom
{
	namespace AssetImporter
	{

		template <>
		std::optional <Asset::asset_type_t<Asset::AssetType::FONT>> ReadAssetFile<Asset::AssetType::FONT>(std::filesystem::path path)
		{
			return {};
		}

	}
}