#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/ShaderAsset.h"

#include "../../../Helper/TextImporter.h"

namespace doom
{
	namespace assetimporter
	{

		template<>
		inline std::optional<Asset::asset_type_t<Asset::eAssetType::SHADER>> ImportSpecificAsset<Asset::eAssetType::SHADER>(const std::filesystem::path& path)
		{
			return GetTextFromFile(path);
		}

	}
}