#include "AssetImporterWorker_Text.h"

#include "../../../Helper/TextImporter.h"

namespace doom
{
	namespace assetimporter
	{
		extern template class AssetApiImporter<Asset::eAssetType::TEXT>;

		template std::optional <Asset::asset_type_t<Asset::eAssetType::TEXT>> ImportSpecificAsset<Asset::eAssetType::TEXT>(const std::filesystem::path&);

		template<>
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXT>> ImportSpecificAsset<Asset::eAssetType::TEXT>(const std::filesystem::path& path)
		{
			return GetTextFromFile(path);
		}
	}
}