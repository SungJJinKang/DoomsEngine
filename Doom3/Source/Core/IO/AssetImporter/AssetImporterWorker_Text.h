#pragma once

#include <filesystem>
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextAsset.h"

#include "../../../Helper/TextImporter.h"

namespace Doom
{
	namespace AssetImporter
	{
		template<>
		inline std::optional <Asset::asset_type_t<Asset::AssetType::TEXT>> ReadAssetFile<Asset::AssetType::TEXT>(std::filesystem::path path)
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