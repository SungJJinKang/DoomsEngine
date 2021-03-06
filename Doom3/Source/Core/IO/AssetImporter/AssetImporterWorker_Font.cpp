#include "AssetImporterWorker_Font.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::FONT>;

bool doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::FONT>::ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::FONT>& asset)
{
	return false;
}