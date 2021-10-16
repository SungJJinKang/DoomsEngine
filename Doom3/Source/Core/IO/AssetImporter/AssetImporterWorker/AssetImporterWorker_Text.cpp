#include "AssetImporterWorker_Text.h"

#include <utility/TextImporter.h>
#include <Asset/TextAsset.h>


bool doom::assetimporter::AssetImporterWorker_Text::ImportSpecificAsset
(
	const std::filesystem::path& path, 
	doom::asset::Asset* asset
)
{
	std::string text{};
	bool isSuccess = GetTextFromFile(path, text);
	if (isSuccess)
	{
		static_cast<doom::asset::TextAsset*>(asset)->SetText(text);
		return true;
	}
	else
	{
		return false;
	}
}

doom::asset::eAssetType doom::assetimporter::AssetImporterWorker_Text::GetEAssetType() const
{
	return doom::asset::eAssetType::TEXT;
}
