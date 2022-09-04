#pragma once
#include <string>
#include <memory>

#include "Asset.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include <Rendering/Buffer/Mesh/FMeshRawData.h>
#include <Rendering/Buffer/Mesh/Mesh.h>

#include "ThreeDModelAsset.reflection.h"
D_NAMESPACE(dooms)
namespace dooms
{
	struct DOOM_API FMeshNode
	{
		std::string MeshNodeName{};
		FMeshNode* ParentMeshNode = nullptr; // Parent node will be deleted later
		std::vector<FMeshNode> MeshNodeChildrenList{};
		
		/// <summary>
		///	Index Of MeshRawDataList
		/// ThreeDModelAsset->MeshRawDataList[mModelMeshIndexs[0]]
		/// </summary>
		std::vector<UINT32> ModelMeshIndexList{};
	};
	

	namespace assetImporter
	{
		class AssetImporterWorker_THREE_D_MODEL;
	}

	namespace asset
	{
		class DOOM_API D_CLASS ThreeDModelAsset : public Asset
		{
			GENERATE_BODY()
				
			friend class ::dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL;

		private:
			
			std::unique_ptr<FMeshNode> Root3DModelNode{};

			/**
			 * \brief This variable has one to one relationship with MeshList
			 */
			std::vector<graphics::FMeshRawData> MeshRawDataList;

			/// <summary>
			/// This variable has one to one relationship with MeshRawDataList
			/// </summary>
			D_PROPERTY()
			std::vector<graphics::Mesh*> MeshList{};
			
			void CreateMesh();
			void ClearMeshData();

			void OnEndImportInMainThread_Internal() final;


		public:
			
			ThreeDModelAsset() = default;
			ThreeDModelAsset(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset
			(
				std::vector<graphics::FMeshRawData>&& MeshRawData,
				std::unique_ptr<FMeshNode>&& RootMeshNode
			) noexcept;
			ThreeDModelAsset(ThreeDModelAsset&& threeDAsset) noexcept = default;
			ThreeDModelAsset& operator=(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset& operator=(ThreeDModelAsset&& threeDAsset) noexcept = default;
			~ThreeDModelAsset();
			virtual void OnSetPendingKill() override;

			/// <summary>
			/// why const? to protect asset data
			/// </summary>
			/// <returns></returns>
			const std::vector<graphics::Mesh*>& GetMeshes() const;
			graphics::Mesh* GetMesh(UINT32 index);
			size_t GetMeshCount() const;
			
			virtual dooms::asset::eAssetType GetEAssetType() const final;
		};

	}
}


