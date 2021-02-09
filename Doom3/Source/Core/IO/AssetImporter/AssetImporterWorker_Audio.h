#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/AudioAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class AssetImporterWorker<eAssetType::AUDIO>
		{
			friend class Assetimporter;
		private:

			static std::optional<Asset::asset_type_t<eAssetType::AUDIO>> ImportSpecificAsset(const std::filesystem::path& path)
			{
				return {};
			}
		};
		

	}
}