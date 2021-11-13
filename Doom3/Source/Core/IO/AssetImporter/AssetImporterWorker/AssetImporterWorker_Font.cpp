#include "AssetImporterWorker_Font.h"

assetImporter::AssetImporterWorker_Font::AssetImporterWorker_Font()
{
	AssetImporterWorker::IsInitialized = true;
}

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
