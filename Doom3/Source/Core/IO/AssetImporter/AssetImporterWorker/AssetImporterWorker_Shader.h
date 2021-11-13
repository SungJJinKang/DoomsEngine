#pragma once

#include "AssetImporterWorker.h"

#include "AssetImporterWorker_Shader.reflection.h"
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
			GENERATE_BODY()
			
			
		private:

			bool ImportShaderAsset(const std::filesystem::path& path, dooms::asset::ShaderAsset* const asset);

		public:

			AssetImporterWorker_Shader();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}