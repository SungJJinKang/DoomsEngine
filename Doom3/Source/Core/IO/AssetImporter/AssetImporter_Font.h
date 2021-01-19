#pragma once
#include "AssetImporterBase.h"
#include "../../Asset/FontAsset.h"

using namespace Doom;


template <>
std::optional <Asset::AssetTypeConditional_t<Asset::AssetType::FONT>> Doom::AssetImporter<Asset::AssetType::FONT>::ReadAssetFile(std::filesystem::path path, AssetImporter<Asset::AssetType::FONT>* assetImporter)
{
	return {};
}