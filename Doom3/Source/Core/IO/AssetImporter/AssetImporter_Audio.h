#pragma once
#include "AssetImporterBase.h"
#include "../../Asset/AudioAsset.h"

using namespace Doom;



template <>
std::optional <Asset::AssetTypeConditional_t<Asset::AssetType::AUDIO>> Doom::AssetImporter<Asset::AssetType::AUDIO>::ReadAssetFile(std::filesystem::path path, AssetImporter<Asset::AssetType::AUDIO>* assetImporter)
{
	return {};
}