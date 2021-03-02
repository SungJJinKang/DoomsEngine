#include "AssetImporterWorker_Shader.h"

#include "../../../Helper/TextImporter.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<eAssetType::SHADER>;

std::optional<Asset::asset_type_t<eAssetType::SHADER>> doom::assetimporter::AssetImporterWorker<eAssetType::SHADER>::ImportSpecificAsset(const std::filesystem::path& path)
{
	return GetTextFromFile(path);
}