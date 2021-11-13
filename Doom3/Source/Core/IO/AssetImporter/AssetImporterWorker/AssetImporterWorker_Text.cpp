#include "AssetImporterWorker_Text.h"

#include <utility/TextImporter.h>
#include <Asset/TextAsset.h>


dooms::assetImporter::AssetImporterWorker_Text::AssetImporterWorker_Text()
{
	AssetImporterWorker::IsInitialized = true;
}

bool dooms::assetImporter::AssetImporterWorker_Text::ImportSpecificAsset
(
	const std::filesystem::path& path, 
	dooms::asset::Asset* asset
)
{
	std::string text{};
	bool isSuccess = GetTextFromFile(path, text);
	if (isSuccess)
	{
		static_cast<dooms::asset::TextAsset*>(asset)->SetText(text);
		return true;
	}
	else
	{
		return false;
	}
}

dooms::asset::eAssetType dooms::assetImporter::AssetImporterWorker_Text::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXT;
}
