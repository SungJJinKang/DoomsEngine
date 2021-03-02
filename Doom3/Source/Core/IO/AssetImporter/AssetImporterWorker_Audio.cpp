#include "AssetImporterWorker_Audio.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<eAssetType::AUDIO>;

std::optional<Asset::asset_type_t<eAssetType::AUDIO>> doom::assetimporter::AssetImporterWorker<eAssetType::AUDIO>::ImportSpecificAsset(const std::filesystem::path& path)
{
	return {};
}