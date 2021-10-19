#pragma once

#include "AssetImporterWorker.h"

#include <API/ASSIMP.h>

struct aiScene;
struct aiNode;
namespace doom
{
	struct ThreeDModelMesh;
	struct ThreeDModelNode;
	namespace asset
	{
		class ThreeDModelAsset;
	}


	namespace assetimporter
	{
		class DOOM_API AssetImporterWorker_THREE_D_MODEL : public AssetImporterWorker
		{
			DOBJECT_CLASS_BODY(AssetImporterWorker_THREE_D_MODEL, doom::eDOBJECT_ClassFlags::NonCopyable);

		private:

			
			/// <summary>
			/// query this value at InitAssetImport
			/// </summary>
			static inline std::string mAssFileFormatId{};

			void ExportToAssFile(const std::filesystem::path& path, const aiScene* pScene);
			void Creat3DModelAsset(const aiScene* pScene, ::doom::asset::ThreeDModelAsset* asset);
			void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ::doom::asset::ThreeDModelAsset* modelAsset, const aiScene* assimpScene);
			bool ImportThreeDModelAsset(const std::filesystem::path& path, ::doom::asset::ThreeDModelAsset* asset);
			void InitializeAssimp();

			Assimp::Importer mAssimpImporter;

		public:

			
			AssetImporterWorker_THREE_D_MODEL();
			AssetImporterWorker_THREE_D_MODEL(const AssetImporterWorker_THREE_D_MODEL&) = delete;
			AssetImporterWorker_THREE_D_MODEL(AssetImporterWorker_THREE_D_MODEL&&) noexcept = default;
			AssetImporterWorker_THREE_D_MODEL& operator=(const AssetImporterWorker_THREE_D_MODEL&) = delete;
			AssetImporterWorker_THREE_D_MODEL& operator=(AssetImporterWorker_THREE_D_MODEL&&) noexcept = default;
			

			/// <summary>
			/// only this file format is acceptable.
			/// if 3d model file doesn't have this format, postprocess and export it as this format
			/// </summary>
			static inline const std::string MAIN_3D_MODEL_FILE_FORMAT{ ".assbin" };
			static const UINT32 ASSIMP_IMPORT_PROCESSING_SETTING;
			static const UINT32 ASSIMP_EXPORT_PROCESSING_SETTING;

			static void SetAssFileFormatId(const char* id);

			virtual bool ImportSpecificAsset(const std::filesystem::path& path, doom::asset::Asset* asset) override;

			virtual doom::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic();
		};
		

		
	}

	

}