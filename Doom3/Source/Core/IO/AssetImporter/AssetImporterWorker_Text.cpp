#include "AssetImporterWorker_Text.h"

#include "../../../Helper/TextImporter.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<eAssetType::TEXT>;

std::optional<Asset::asset_type_t<eAssetType::TEXT>> doom::assetimporter::AssetImporterWorker<eAssetType::TEXT>::ImportSpecificAsset(const std::filesystem::path& path)
{
	return GetTextFromFile(path);
}