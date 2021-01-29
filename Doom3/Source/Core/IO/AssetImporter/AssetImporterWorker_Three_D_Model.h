#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include "../../API/ASSIMP.h"
#include "../../Asset/ThreeDModelAsset.h"



#include <thread>

namespace doom
{
	namespace assetimporter
	{
		template <> struct api_importer_type<Asset::eAssetType::THREE_D_MODEL> { using type = typename Assimp::Importer; };

		template<>
		void AssetApiImporter<Asset::eAssetType::THREE_D_MODEL>::InitApiImporter(api_importer_type_t<Asset::eAssetType::THREE_D_MODEL>& apiImporter);

		/// Create Nodes Recursively
		/// </summary>
		/// <param name="currentNode"></param>
		/// <param name="currentAssimpNode"></param>
		/// <param name="parentNode"></param>
		/// <param name="modelAsset"></param>
		/// <param name="assimpScene"></param>
		/// <returns></returns>
		void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene);


#ifdef DEBUG_MODE
		class AssimpLogStream : public Assimp::LogStream {
		public:
			// Write womethink using your own functionality
			inline void write(const char* message)
			{
				DEBUG_LOG({ "Assimp Debugger : ", message });
			}


		};
#endif


		template<>
		std::optional<Asset::asset_type_t<Asset::eAssetType::THREE_D_MODEL>> ReadAssetFile<Asset::eAssetType::THREE_D_MODEL>(std::filesystem::path path);
		

	}

	

}