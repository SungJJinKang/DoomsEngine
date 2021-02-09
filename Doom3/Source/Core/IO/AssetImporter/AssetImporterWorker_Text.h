#pragma once

#include <filesystem>
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextAsset.h"


namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<eAssetType::TEXT>
		{
			friend class Assetimporter;
		private:
			static std::optional <Asset::asset_type_t<eAssetType::TEXT>> ImportSpecificAsset(const std::filesystem::path& path)
			{
				return GetTextFromFile(path);
			}
		};


	}
}