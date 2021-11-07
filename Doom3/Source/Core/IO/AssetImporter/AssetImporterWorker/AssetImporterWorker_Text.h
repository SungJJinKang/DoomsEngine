#pragma once

#include <filesystem>
#include "AssetImporterWorker.h"

namespace dooms
{
	namespace assetImporter
	{
		class DOOM_API AssetImporterWorker_Text : public AssetImporterWorker
		{
			DOBJECT_CLASS_BODY(AssetImporterWorker_Text);
			DOBJECT_CLASS_BASE_CHAIN(AssetImporterWorker)

		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}