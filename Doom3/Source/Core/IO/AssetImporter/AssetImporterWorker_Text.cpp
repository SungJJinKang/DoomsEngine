#include "AssetImporterWorker_Text.h"

#include "../../../Helper/TextImporter.h"

namespace doom
{
	namespace assetimporter
	{
		extern template class AssetApiImporter<Asset::eAssetType::TEXT>;

		template std::optional <Asset::asset_type_t<Asset::eAssetType::TEXT>> ReadAssetFile<Asset::eAssetType::TEXT>(std::filesystem::path path);

		template<>
		std::optional <Asset::asset_type_t<Asset::eAssetType::TEXT>> ReadAssetFile<Asset::eAssetType::TEXT>(std::filesystem::path path)
		{
			auto str = GetTextFromFile(path);
			if (str.has_value())
			{
				return *str;
			}
			else
			{
				return {};
			}
		}
	}
}