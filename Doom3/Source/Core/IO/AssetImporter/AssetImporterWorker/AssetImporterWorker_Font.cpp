#include "AssetImporterWorker_Font.h"

bool assetImporter::AssetImporterWorker_Font::ImportSpecificAsset
(
	const std::filesystem::path& paths,
	dooms::asset::Asset* asset
)
{
	return false;
}

dooms::asset::eAssetType assetImporter::AssetImporterWorker_Font::GetEAssetType() const
{
	return dooms::asset::eAssetType::FONT;
}
