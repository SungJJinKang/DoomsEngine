#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetImporterBase.h"
#include "../../Asset/TextureAsset.h"

using namespace Doom;


template <>
std::optional <Asset::AssetTypeConditional_t<Asset::AssetType::TEXTURE>> Doom::AssetImporter<Asset::AssetType::TEXTURE>::ReadAssetFile(std::filesystem::path path, AssetImporter<Asset::AssetType::TEXTURE>* assetImporter)
{
	return {};
}