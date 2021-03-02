#pragma once
#include "AssetApiImporter.h"
#include "AssetImporterWorker_Base.h"

#include <utility>
#include "../../API/ASSIMP.h"
#include "../../Asset/ThreeDModelAsset.h"




namespace doom
{
	class GameCore;
	namespace assetimporter
	{
		template <> struct api_importer_type<eAssetType::THREE_D_MODEL> { using type = typename Assimp::Importer; };
		
		template<>
		void AssetApiImporter<eAssetType::THREE_D_MODEL>::InitApiImporter(api_importer_type_t<eAssetType::THREE_D_MODEL>& apiImporter);


		template <>
		class AssetImporterWorker<eAssetType::THREE_D_MODEL>
		{
			friend class GameCore;
			friend class Assetimporter;
#ifdef DEBUG_MODE
			class AssimpLogStream : public Assimp::LogStream {
			public:
				// Write womethink using your own functionality
				inline void write(const char* message)
				{
					D_DEBUG_LOG({ "Assimp Debugger : ", message });
				}
			};
#endif

		private:

			static void InitSetting();
			static std::optional<Asset::asset_type_t<eAssetType::THREE_D_MODEL>> ImportSpecificAsset(const std::filesystem::path& path);
			/// Create Nodes Recursively
			/// </summary>
			/// <param name="currentNode"></param>
			/// <param name="currentAssimpNode"></param>
			/// <param name="parentNode"></param>
			/// <param name="modelAsset"></param>
			/// <param name="assimpScene"></param>
			/// <returns></returns>
			static void SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene);

		};

		
		extern template class AssetApiImporter<eAssetType::THREE_D_MODEL>;
		extern template class AssetImporterWorker<eAssetType::THREE_D_MODEL>;


		
	}

	

}