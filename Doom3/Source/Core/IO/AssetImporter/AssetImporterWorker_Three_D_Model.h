#pragma once

#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include <assimp/Importer.hpp> 
#include "../../Asset/ThreeDModelAsset.h"

struct aiScene;
struct aiNode;
namespace doom
{
	class GameCore;
	namespace assetimporter
	{
		template <> struct api_importer_type<::doom::asset::eAssetType::THREE_D_MODEL> { using type = typename Assimp::Importer; };
		
		template<>
		void AssetApiImporter<::doom::asset::eAssetType::THREE_D_MODEL>::InitApiImporter(api_importer_type_t<::doom::asset::eAssetType::THREE_D_MODEL>& apiImporter);

		template <>
		void InitAssetImport<::doom::asset::eAssetType::THREE_D_MODEL>();
		template <>
		void EndAssetImport<::doom::asset::eAssetType::THREE_D_MODEL>();

		template <>
		class DOOM_API AssetImporterWorker<::doom::asset::eAssetType::THREE_D_MODEL>
		{
			friend class GameCore;
			friend class Assetimporter;

		private:

			
			/// <summary>
			/// query this value at InitAssetImport
			/// </summary>
			static inline std::string mAssFileFormatId{};

			static void ExportToAssFile(const std::filesystem::path& path, const aiScene* pScene);
		

			static void Creat3DModelAsset(const aiScene* pScene, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::THREE_D_MODEL>& asset);

			static bool ImportSpecificAsset(const std::filesystem::path& path, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::THREE_D_MODEL>& asset);
			/// Create Nodes Recursively
			/// </summary>
			/// <param name="currentNode"></param>
			/// <param name="currentAssimpNode"></param>
			/// <param name="parentNode"></param>
			/// <param name="modelAsset"></param>
			/// <param name="assimpScene"></param>
			/// <returns></returns>
			static void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ::doom::asset::Asset::asset_type_t<::doom::asset::eAssetType::THREE_D_MODEL>& modelAsset, const aiScene* assimpScene);

		public:
			/// <summary>
			/// only this file format is acceptable.
			/// if 3d model file doesn't have this format, postprocess and export it as this format
			/// </summary>
			static inline const std::string MAIN_3D_MODEL_FILE_FORMAT{ ".assbin" };
			static const unsigned int ASSIMP_IMPORT_PROCESSING_SETTING;
			static const unsigned int ASSIMP_EXPORT_PROCESSING_SETTING;

			static void SetAssFileFormatId(const char* id);
		};

		
		

		extern template class AssetApiImporter<::doom::asset::eAssetType::THREE_D_MODEL>;
		extern template class AssetImporterWorker<::doom::asset::eAssetType::THREE_D_MODEL>;


		
	}

	

}