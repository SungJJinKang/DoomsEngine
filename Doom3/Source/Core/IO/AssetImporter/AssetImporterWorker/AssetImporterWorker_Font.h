#pragma once

#include "AssetImporterWorker.h"

using namespace doom;

namespace doom
{
	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker_Font : public AssetImporterWorker
		{
		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;
			virtual doom::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
		
	}
}