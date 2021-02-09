#pragma once
#include "../../API/STB_IMAGE.h"

#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/TextureAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<eAssetType::TEXTURE>
		{
			friend class Assetimporter;
		private:
			static std::optional <Asset::asset_type_t<eAssetType::TEXTURE>> ImportSpecificAsset(const std::filesystem::path& path)
			{
				return {};
			}
		};
	
	}
}