#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/ShaderAsset.h"

#include "../../../Helper/TextImporter.h"

namespace Doom
{
	namespace AssetImporter
	{

		template<>
		inline std::optional<Asset::asset_type_t<Asset::AssetType::SHADER>> ReadAssetFile<Asset::AssetType::SHADER>(std::filesystem::path path)
		{
			auto str = GetTextFromFile(path);
			if (str.has_value())
			{
				return str.value();
			}
			else
			{
				return {};
			}
		}

	}
}