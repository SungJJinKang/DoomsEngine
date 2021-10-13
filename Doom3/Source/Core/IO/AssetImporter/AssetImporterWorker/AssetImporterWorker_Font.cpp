#include "AssetImporterWorker_Font.h"

bool assetimporter::AssetImporterWorker_Font::ImportSpecificAsset
(
	const std::filesystem::path& paths,
	doom::asset::Asset* asset
)
{
	return false;
}

doom::asset::eAssetType assetimporter::AssetImporterWorker_Font::GetEAssetType() const
{
	return doom::asset::eAssetType::FONT;
}
