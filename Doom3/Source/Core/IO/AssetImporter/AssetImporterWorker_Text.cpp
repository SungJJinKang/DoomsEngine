#include "AssetImporterWorker_Text.h"

#include "../../../Helper/TextImporter.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::TEXT>;

bool doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::TEXT>::ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::TEXT>& asset)
{
	std::string text{};
	bool isSuccess = GetTextFromFile(path, text);
	if (isSuccess)
	{
		asset.SetText(text);
		return true;
	}
	else
	{
		return false;
	}
}