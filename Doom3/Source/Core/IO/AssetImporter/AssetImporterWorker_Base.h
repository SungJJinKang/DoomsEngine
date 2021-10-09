#pragma once
#include <optional>

#include "../../Core.h"

#include "../../Asset/Asset.h"


namespace doom
{
	namespace assetimporter
	{
		template <::doom::asset::eAssetType assetType>
		void InitAssetImport() {}

		template <::doom::asset::eAssetType assetType>
		void EndAssetImport() {}

		template <::doom::asset::eAssetType assetType>
		class DOOM_API AssetImporterWorker
		{
			friend class Assetimporter;
		private:
			static bool ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<assetType>& asset);
			
		};
		
	}
}