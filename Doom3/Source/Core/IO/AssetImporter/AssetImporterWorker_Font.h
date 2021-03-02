#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/FontAsset.h"

using namespace doom;

namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<eAssetType::FONT>
		{
			friend class Assetimporter;
		private:
			static std::optional <Asset::asset_type_t<eAssetType::FONT>> ImportSpecificAsset(const std::filesystem::path& path);
		};

		extern template class AssetApiImporter<eAssetType::FONT>;
	}
}