#pragma once

#include <filesystem>
#include "AssetImporterWorker.h"
#include "../../Asset/TextAsset.h"

#include "../../../Helper/TextImporter.h"

namespace Doom
{
	namespace AssetImporter
	{

		

		template<>
		std::optional <Asset::asset_type_t<Asset::AssetType::TEXT>> ReadAssetFile<Asset::AssetType::TEXT>(std::filesystem::path path)
		{
			auto str = GetTextFromFile(path);
			if (str.has_value())
			{
				return *str;
			}
			else
			{
				return {};
			}
		}
	}
}