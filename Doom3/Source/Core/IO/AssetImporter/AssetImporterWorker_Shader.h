#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/ShaderAsset.h"

#include "../../../Helper/TextImporter.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<Asset::eAssetType::SHADER>
		{
			friend class Assetimporter;
		private:
			static std::optional<Asset::asset_type_t<Asset::eAssetType::SHADER>> ImportSpecificAsset(const std::filesystem::path& path)
			{
				return GetTextFromFile(path);
			}
		};
		

	}
}