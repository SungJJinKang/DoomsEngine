#pragma once

#include "AssetImporterWorker.h"

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Asset/ShaderAsset.h>

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

			bool IsEssentialEngineShaderFilesExist(const std::filesystem::path& assetPath) const;
			bool ImportShaderAsset(const std::filesystem::path& assetPath, dooms::asset::ShaderAsset* const asset);
			std::array<asset::ShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> LoadShaderTextDatas(const std::filesystem::path& assetPath) const;

		public:

			AssetImporterWorker_Shader();

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic() {}
		};
	}
}
