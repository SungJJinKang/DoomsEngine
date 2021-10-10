#pragma once

#include <filesystem>
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class DOOM_API AssetImporterWorker<::doom::asset::eAssetType::TEXT>
		{
			friend class Assetimporter;
		private:
			static bool ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::TEXT>& asset);
		};

		extern template class AssetApiImporter<::doom::asset::eAssetType::TEXT>;
	}
}