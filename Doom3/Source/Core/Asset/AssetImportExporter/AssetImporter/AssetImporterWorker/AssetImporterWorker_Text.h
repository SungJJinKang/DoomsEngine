#pragma once

#include <filesystem>
#include "AssetImporterWorker.h"

#include "AssetImporterWorker_Text.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker_Text : public AssetImporterWorker
		{
			GENERATE_BODY()
			

		public:

			AssetImporterWorker_Text();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}