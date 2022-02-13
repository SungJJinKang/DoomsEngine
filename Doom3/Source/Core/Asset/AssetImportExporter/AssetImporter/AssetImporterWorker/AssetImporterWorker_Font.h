#pragma once

#include "AssetImporterWorker.h"

using namespace dooms;

#include "AssetImporterWorker_Font.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker_Font : public AssetImporterWorker
		{
			GENERATE_BODY()
			

		public:

			AssetImporterWorker_Font();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;
			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
		
	}
}