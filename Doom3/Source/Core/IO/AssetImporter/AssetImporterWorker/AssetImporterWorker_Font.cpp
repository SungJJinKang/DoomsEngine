#include "AssetImporterWorker_Font.h"

bool assetImporter::AssetImporterWorker_Font::ImportSpecificAsset
(
	const std::filesystem::path& paths,
	doom::asset::Asset* asset
)
{
	return false;
}

doom::asset::eAssetType assetImporter::AssetImporterWorker_Font::GetEAssetType() const
{
	return doom::asset::eAssetType::FONT;
}
