#pragma once

#include "AssetImporterWorker.h"

#include "AssetImporterWorker_Audio.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker_Audio : public AssetImporterWorker
		{
			GENERATE_BODY()

		public:

			AssetImporterWorker_Audio();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;
			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
		
	}
}