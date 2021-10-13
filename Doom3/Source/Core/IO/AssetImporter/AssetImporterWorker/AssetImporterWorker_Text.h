#pragma once

#include <filesystem>
#include "AssetImporterWorker.h"

namespace doom
{
	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker_Text : public AssetImporterWorker
		{
		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;

			virtual doom::asset::eAssetType GetEAssetType() const final;
		};
	}
}