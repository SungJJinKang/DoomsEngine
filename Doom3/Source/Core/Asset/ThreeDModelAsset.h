#pragma once
#include <string>

#include "Asset.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

using namespace math;


#include "ThreeDModelAsset.reflection.h"
D_NAMESPACE(dooms)
namespace dooms
{
	struct DOOM_API FMeshNode
	{
		std::string mName;
		FMeshNode* mThreeDModelNodeParent = nullptr; // Parent node will be deleted later
		std::vector<FMeshNode> mThreeDModelNodeChildrens;
		
		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		std::vector<UINT32> mModelMeshIndexs;
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
			
			FMeshNode* mRootModelNode{};

			D_PROPERTY()
			std::vector<ThreeDModelMesh> mModelMeshAssets;

			///////////

			D_PROPERTY()
			FMeshNode* mRootMeshNode{nullptr};

			D_PROPERTY()
			std::vector<graphics::Mesh> mMeshes{};

			D_PROPERTY()
				size_t mNumOfMeshes{};

			/// <summary>
			/// Send Meshdata to GPU
			/// GPU Buffer
			/// </summary>
			void SendMeshDataToGPU();

			void ClearMeshData();
			void CreateNode(graphics::MeshNode* currentNode, FMeshNode* currentModelNodeAsset);
			void OnEndImportInMainThread_Internal() final;


		public:
			
			ThreeDModelAsset() = default;
			ThreeDModelAsset(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset
			(
				std::vector<ThreeDModelMesh>&& threeDModelMeses, 
				FMeshNode* const rootThreeDModelNode
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
			const std::vector<graphics::Mesh>& GetMeshes() const;
			graphics::Mesh* GetMesh(UINT32 index);
			size_t GetMeshCount() const;


			virtual dooms::asset::eAssetType GetEAssetType() const final;
		};

	}
}


