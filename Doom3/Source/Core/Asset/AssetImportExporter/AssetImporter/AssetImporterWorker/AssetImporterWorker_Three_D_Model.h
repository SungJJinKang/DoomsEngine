#pragma once

#include "AssetImporterWorker.h"

#include <API/ASSIMP.h>


#include "AssetImporterWorker_Three_D_Model.reflection.h"
struct aiScene;
struct aiNode;
struct aiMesh;
namespace dooms
{
	class ThreeDModelMesh;
	class FMeshNode;
	namespace asset
	{
		class ThreeDModelAsset;
	}


	namespace assetImporter
	{
		class DOOM_API D_CLASS AssetImporterWorker_THREE_D_MODEL : public AssetImporterWorker
		{
			GENERATE_BODY()
			

		private:
#ifdef DEBUG_MODE
			static void ClearAssimpLooger();
#endif
			void Creat3DModelAsset(const aiScene* pScene, ::dooms::asset::ThreeDModelAsset* ModelAsset);
			void SetMeshNodeData(FMeshNode* CurrentMeshNode, aiNode* CurrentAssimpMeshNode, FMeshNode* ParentMeshNode, ::dooms::asset::ThreeDModelAsset* ModelAsset, const aiScene* AssimpScene);
			bool ImportThreeDModelAsset(const std::filesystem::path& path, ::dooms::asset::ThreeDModelAsset* asset);
			void InitializeAssimp();

			bool IsValidMesh(const aiMesh* const assimpMesh);

			Assimp::Importer mAssimpImporter;

		public:

			
			AssetImporterWorker_THREE_D_MODEL();
			AssetImporterWorker_THREE_D_MODEL(const AssetImporterWorker_THREE_D_MODEL&) = delete;
			AssetImporterWorker_THREE_D_MODEL(AssetImporterWorker_THREE_D_MODEL&&) noexcept = default;
			AssetImporterWorker_THREE_D_MODEL& operator=(const AssetImporterWorker_THREE_D_MODEL&) = delete;
			AssetImporterWorker_THREE_D_MODEL& operator=(AssetImporterWorker_THREE_D_MODEL&&) noexcept = default;
			~AssetImporterWorker_THREE_D_MODEL();

			/// <summary>
			/// only this file format is acceptable.
			/// if 3d model file doesn't have this format, postprocess and export it as this format
			/// </summary>
			static inline const std::string MAIN_3D_MODEL_FILE_FORMAT{ ".assbin" };
			static const UINT32 ASSIMP_IMPORT_PROCESSING_SETTING;
			static const UINT32 ASSIMP_EXPORT_PROCESSING_SETTING;


			virtual bool ImportSpecificAsset(const std::filesystem::path& path, dooms::asset::Asset* asset) override;

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			static void InitializeAssetImporterWorkerStatic();
			static void UnInitializeAssetImporterWorkerStatic();
		};
		

		
	}

	

}