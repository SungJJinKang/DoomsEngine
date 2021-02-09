#pragma once
#include <optional>

#include "../../Core.h"

#include "../../Asset/Asset.h"


namespace doom
{
	namespace assetimporter
	{
		template <eAssetType assetType>
		class AssetImporterWorker
		{
			friend class Assetimporter;
		private:
			static std::optional<Asset::asset_type_t<assetType>> ImportSpecificAsset(const std::filesystem::path& path);
		};
		
	}
}