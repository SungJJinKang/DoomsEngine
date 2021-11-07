#pragma once
#include <string>

#include "Asset.h"

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"
#include "../Graphics/ePrimitiveType.h"
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

using namespace math;




namespace dooms
{
	struct ThreeDModelMesh;
	struct ThreeDModelNode;

	namespace asset
	{
		class ThreeDModelAsset;
	}


	/// <summary>
	/// layout(location = 0) in vec3 aPos;
	/// layout(location = 1) in vec2 aUV0;
	/// layout(location = 2) in vec3 aNormal;
	/// layout(location = 3) in vec3 aTangent;
	/// layout(location = 4) in vec3 aBitangent;
	/// 
	/// Never edit this struct, Never change placement order of datas
	/// </summary>
	struct MeshVertexData
	{
		Vector3 mVertex;
		Vector2 mTexCoord; //support only one channel
		Vector3 mNormal;
		Vector3 mTangent;
		Vector3 mBitangent;

		MeshVertexData() = default;
		MeshVertexData(const MeshVertexData&) = default;
		MeshVertexData(MeshVertexData&&) noexcept = default;
		MeshVertexData& operator=(const MeshVertexData&) = default;
		MeshVertexData& operator=(MeshVertexData&&) noexcept = default;
		~MeshVertexData() = default;
	};

	/*
	struct MeshFaceData
	{
		UINT32 mNumIndices;
		UINT32* mIndices;
	};
	*/

	
	struct ThreeDModelMesh
	{
		std::string mName;

		ePrimitiveType mPrimitiveType;

		bool bHasIndices;
		UINT32 mNumOfIndices;
		/// <summary>
		/// mMeshIndices count is mNumOfIndiecs
		/// </summary>
		std::unique_ptr<UINT32[]> mMeshIndices;

		UINT32 mNumOfVertexs;
		/// <summary>
		/// mMeshVertexDatas count is mNumOfVertices
		/// Vertices data is packed
		/// 
		/// ( O ) Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent
		/// ( X ) Vertex Vertex Vertex | TexCoord TexCoord TexCoord | Normal Normal Normal | Tangent Tangent Tangent | Bitangent Bitangent Bitangent
		/// </summary>
		std::unique_ptr<MeshVertexData[]> mMeshVertexDatas;

		physics::AABB3D mAABB3D;
		physics::Sphere mSphere;

		ThreeDModelMesh() = default;
		ThreeDModelMesh(const ThreeDModelMesh&) = delete;
		ThreeDModelMesh(ThreeDModelMesh&&) noexcept = default;
		ThreeDModelMesh& operator=(const ThreeDModelMesh&) = delete;
		ThreeDModelMesh& operator=(ThreeDModelMesh&&) noexcept = default;
		~ThreeDModelMesh() = default;
	};

	struct ThreeDModelNode
	{ 
		/// <summary>
		/// don't clear this
		/// </summary>
		dooms::asset::ThreeDModelAsset* mThreeDModelAsset;

		std::string mName;

		/// <summary>
		/// don't clear this
		/// </summary>
		ThreeDModelNode* mThreeDModelNodeParent; // Parent node will be deleted later

		std::unique_ptr<ThreeDModelNode[]> mThreeDModelNodeChildrens;
		UINT32 mNumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		std::unique_ptr<UINT32[]> mModelMeshIndexs;
		UINT32 mNumOfModelMeshes;

		ThreeDModelNode() = default;
		ThreeDModelNode(const ThreeDModelNode&) = delete;
		ThreeDModelNode(ThreeDModelNode&&) noexcept = default;
		ThreeDModelNode& operator=(const ThreeDModelNode&) = delete;
		ThreeDModelNode& operator=(ThreeDModelNode&&) noexcept = default;
		~ThreeDModelNode() = default;
	};

	namespace assetImporter
	{
		class AssetImporterWorker_THREE_D_MODEL;
	}

	namespace asset
	{
		class DOOM_API ThreeDModelAsset : public Asset
		{
			DOBJECT_CLASS_BODY(ThreeDModelAsset, dooms::eDOBJECT_ClassFlags::NonCopyable)
				DOBJECT_CLASS_BASE_CHAIN(Asset)

			friend class ::dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL;

		private:
			std::unique_ptr<ThreeDModelNode> mRootModelNode{};

			std::unique_ptr<ThreeDModelMesh[]> mModelMeshAssets{};
			UINT32 mNumOfModelMeshAssets{};

			///////////

			std::unique_ptr<graphics::MeshNode> mRootMeshNode{};
			std::vector<graphics::Mesh> mMeshes{};

			UINT32 mNumOfMeshes{};

			/// <summary>
			/// Send Meshdata to GPU
			/// GPU Buffer
			/// </summary>
			void SendMeshDataToGPU();

			void ClearMeshData();
			void CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset);
			void OnEndImportInMainThread_Internal() final;


		public:
			
			ThreeDModelAsset() = default;
			ThreeDModelAsset(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset(ThreeDModelAsset&& threeDAsset) noexcept = default;
			ThreeDModelAsset& operator=(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset& operator=(ThreeDModelAsset&& threeDAsset) noexcept = default;
			~ThreeDModelAsset();

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


