#include "AssetImporterWorker_Audio.h"

dooms::assetImporter::AssetImporterWorker_Audio::AssetImporterWorker_Audio()
{
	AssetImporterWorker::IsInitialized = true;
}

bool dooms::assetImporter::AssetImporterWorker_Audio::ImportSpecificAsset
(
	const std::filesystem::path& path,
	dooms::asset::Asset* asset
)
{
	return false;
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_Audio::GetEAssetType() const
{
	return dooms::asset::eAssetType::AUDIO;
}
