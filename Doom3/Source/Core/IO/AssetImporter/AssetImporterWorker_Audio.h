#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../Asset/AudioAsset.h"

namespace doom
{
	namespace assetimporter
	{
		template <>
		class DOOM_API AssetImporterWorker<::doom::asset::eAssetType::AUDIO>
		{
			friend class Assetimporter;
		private:

			static bool ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::AUDIO>& asset);
		};
		
		extern template class AssetApiImporter<::doom::asset::eAssetType::AUDIO>;
	}
}