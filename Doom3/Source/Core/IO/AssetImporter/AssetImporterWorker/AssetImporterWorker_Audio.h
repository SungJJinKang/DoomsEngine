#pragma once

#include "AssetImporterWorker.h"


namespace doom
{
	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker_Audio : public AssetImporterWorker
		{

		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;
			virtual doom::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
		
	}
}