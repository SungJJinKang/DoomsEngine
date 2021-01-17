#pragma once
#include "AssetImporterBase.h"
#include "../../Asset/AudioAsset.h"

using namespace Doom;

template <> struct AssetTypeConditional<AssetType::AUDIO> { using type = AudioAsset; };
template <> struct ApiImporterTypeConditional<AssetType::AUDIO> { using type = typename DummyApiImporter; };

template <>
std::optional <AssetTypeConditional_t<AssetType::AUDIO>> AssetImporter<AssetType::AUDIO>::ReadAssetFile(std::filesystem::path path, AssetImporter<AssetType::AUDIO>* assetImporter)
{
	return {};
}