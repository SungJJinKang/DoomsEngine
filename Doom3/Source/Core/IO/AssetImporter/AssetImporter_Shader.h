#pragma once

#include "AssetImporterBase.h"
#include "AssetImporter_Text.h"
#include "../../Asset/ShaderAsset.h"

template<>
std::optional <Asset::AssetTypeConditional_t<Asset::AssetType::SHADER>> Doom::AssetImporter<Asset::AssetType::SHADER>::ReadAssetFile(std::filesystem::path path, AssetImporter<Asset::AssetType::SHADER>* assetImporter)
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