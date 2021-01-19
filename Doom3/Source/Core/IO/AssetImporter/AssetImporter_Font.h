#pragma once
#include "AssetImporterBase.h"
#include "../../Asset/FontAsset.h"

using namespace Doom;

template <> struct ApiImporterTypeConditional<AssetType::FONT> { using type = typename DummyApiImporter; };

template <>
std::optional <AssetTypeConditional_t<AssetType::FONT>> AssetImporter<AssetType::FONT>::ReadAssetFile(std::filesystem::path path, AssetImporter<AssetType::FONT>* assetImporter)
{
	return {};
}