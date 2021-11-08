#pragma once

#include "AssetImporterWorker.h"


namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
	}

	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker_Shader : public AssetImporterWorker
		{
			DOBJECT_CLASS_BODY(AssetImporterWorker_Shader);
			DOBJECT_CLASS_BASE_CHAIN(AssetImporterWorker)
			
		private:

			bool ImportShaderAsset(const std::filesystem::path& path, dooms::asset::ShaderAsset* const asset);

		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}