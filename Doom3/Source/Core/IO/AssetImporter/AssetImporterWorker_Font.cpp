#include "AssetImporterWorker_Font.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<eAssetType::FONT>;

std::optional<Asset::asset_type_t<eAssetType::FONT>> doom::assetimporter::AssetImporterWorker<eAssetType::FONT>::ImportSpecificAsset(const std::filesystem::path& path)
{
	return {};
}