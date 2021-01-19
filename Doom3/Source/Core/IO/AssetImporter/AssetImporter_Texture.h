#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetImporterBase.h"
#include "../../Asset/TextureAsset.h"

using namespace Doom;

template <> struct ApiImporterTypeConditional<AssetType::TEXTURE> { using type = typename DummyApiImporter; };

template <>
std::optional <AssetTypeConditional_t<AssetType::TEXTURE>> AssetImporter<AssetType::TEXTURE>::ReadAssetFile(std::filesystem::path path, AssetImporter<AssetType::TEXTURE>* assetImporter)
{
	return {};
}