#include "AssetImporterWorker_Audio.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::AUDIO>;

bool doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::AUDIO>::ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::AUDIO>& asset)
{
	return false;
}