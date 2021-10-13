#pragma once

#include "AssetImporterWorker.h"


namespace doom
{
	namespace asset
	{
		class ShaderAsset;
	}

	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker_Shader : public AssetImporterWorker
		{
		private:

			bool ImportShaderAsset(const std::filesystem::path& path, doom::asset::ShaderAsset* const asset);

		public:

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;

			virtual doom::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}