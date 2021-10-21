#include "AssetImporterWorker_Audio.h"

bool doom::assetImporter::AssetImporterWorker_Audio::ImportSpecificAsset
(
	const std::filesystem::path& path,
	doom::asset::Asset* asset
)
{
	return false;
}

doom::asset::eAssetType doom::assetImporter::AssetImporterWorker_Audio::GetEAssetType() const
{
	return doom::asset::eAssetType::AUDIO;
}
