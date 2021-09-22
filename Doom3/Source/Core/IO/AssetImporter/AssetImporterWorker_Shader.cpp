#include "AssetImporterWorker_Shader.h"

#include "../../../Helper/TextImporter.h"

using namespace doom;
using namespace doom::assetimporter;
template class doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::SHADER>;

bool doom::assetimporter::AssetImporterWorker<::doom::asset::eAssetType::SHADER>::ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::SHADER>& asset)
{
	std::string text{};
	bool isSuccess = GetTextFromFile(path, text);

	D_ASSERT(text.empty() == false);

	if (isSuccess)
	{
		asset.SetShaderText(text, false);
		return true;
	}
	else
	{
		return false;
	}
}