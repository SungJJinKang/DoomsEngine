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
		class AssetImporterWorker<::doom::asset::eAssetType::FONT>
		{
			friend class Assetimporter;
		private:
			static bool ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::FONT>& asset);
		};

		extern template class AssetApiImporter<::doom::asset::eAssetType::FONT>;
	}
}