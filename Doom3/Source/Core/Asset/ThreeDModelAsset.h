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


#include "ThreeDModelAsset.reflection.h"
D_NAMESPACE(dooms)
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
	struct DOOM_API D_STRUCT MeshVertexData
	{
		//GENERATE_BODY_MeshVertexData() // Never Do this. Because data is copied with memcpy in importer

		D_PROPERTY()
		Vector3 mVertex;

		D_PROPERTY()
		Vector2 mTexCoord; //support only one channel

		D_PROPERTY()
		Vector3 mNormal;

		D_PROPERTY()
		Vector3 mTangent;

		D_PROPERTY()
		Vector3 mBitangent;

		MeshVertexData() = default;
		MeshVertexData(int*) {}
		MeshVertexData(const MeshVertexData&) = default;
		MeshVertexData(MeshVertexData&&) noexcept = default;
		MeshVertexData& operator=(const MeshVertexData&) = default;
		MeshVertexData& operator=(MeshVertexData&&) noexcept = default;
		~MeshVertexData() = default;
	};
	D_REFLECTION_TYPE(dooms::MeshVertexData)

	/*
	struct MeshFaceData
	{
		UINT32 mNumIndices;
		UINT32* mIndices;
	};
	*/

	
	struct DOOM_API D_STRUCT ThreeDModelMesh
	{
		//GENERATE_BODY_ThreeDModelMesh() // Never Do this. Because data is copied with memcpy in importer

		D_PROPERTY()
		std::string mName;

		D_PROPERTY()
		ePrimitiveType mPrimitiveType;

		D_PROPERTY()
		bool bHasIndices;

		D_PROPERTY()
		UINT32 mNumOfIndices;

		/// <summary>
		/// mMeshIndices count is mNumOfIndiecs
		/// </summary>
		D_PROPERTY()
		std::vector<UINT32> mMeshIndices;

		D_PROPERTY()
		UINT32 mNumOfVertexs;

		/// <summary>
		/// mMeshVertexDatas count is mNumOfVertices
		/// Vertices data is packed
		/// 
		/// ( O ) Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent
		/// ( X ) Vertex Vertex Vertex | TexCoord TexCoord TexCoord | Normal Normal Normal | Tangent Tangent Tangent | Bitangent Bitangent Bitangent
		/// </summary>
		D_PROPERTY()
		std::vector<MeshVertexData> mMeshVertexDatas;

		D_PROPERTY()
		physics::AABB3D mAABB3D;
		D_PROPERTY()
		physics::Sphere mSphere;

		ThreeDModelMesh() = default;
		ThreeDModelMesh(int*){}
		ThreeDModelMesh(const ThreeDModelMesh&) = default;
		ThreeDModelMesh(ThreeDModelMesh&&) noexcept = default;
		ThreeDModelMesh& operator=(const ThreeDModelMesh&) = default;
		ThreeDModelMesh& operator=(ThreeDModelMesh&&) noexcept = default;
		~ThreeDModelMesh() = default;
	};

	struct DOOM_API D_STRUCT ThreeDModelNode
	{
		//GENERATE_BODY_ThreeDModelNode()

		/// <summary>
		/// don't clear this
		/// </summary>
		dooms::asset::ThreeDModelAsset* mThreeDModelAsset;

		D_PROPERTY()
		std::string mName;

		/// <summary>
		/// don't clear this
		/// </summary>
		D_PROPERTY()
		ThreeDModelNode* mThreeDModelNodeParent; // Parent node will be deleted later

		D_PROPERTY()
		std::vector<ThreeDModelNode> mThreeDModelNodeChildrens;

		D_PROPERTY()
		UINT32 mNumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		D_PROPERTY()
		std::vector<UINT32> mModelMeshIndexs;

		D_PROPERTY()
		UINT32 mNumOfModelMeshes;

		ThreeDModelNode() = default;
		ThreeDModelNode(int*) {}
		ThreeDModelNode(const ThreeDModelNode&) = default;
		ThreeDModelNode(ThreeDModelNode&&) noexcept = default;
		ThreeDModelNode& operator=(const ThreeDModelNode&) = default;
		ThreeDModelNode& operator=(ThreeDModelNode&&) noexcept = default;
		~ThreeDModelNode() = default;
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

			D_PROPERTY()
			std::unique_ptr<ThreeDModelNode> mRootModelNode{};

			D_PROPERTY()
			std::vector<ThreeDModelMesh> mModelMeshAssets{};

			D_PROPERTY()
			UINT32 mNumOfModelMeshAssets{};

			///////////

			D_PROPERTY()
			std::unique_ptr<graphics::MeshNode> mRootMeshNode{};

			D_PROPERTY()
			std::vector<graphics::Mesh> mMeshes{};

			D_PROPERTY()
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
			ThreeDModelAsset(const ThreeDModelAsset&) = default;
			ThreeDModelAsset(ThreeDModelAsset&& threeDAsset) noexcept = default;
			ThreeDModelAsset& operator=(const ThreeDModelAsset&) = default;
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


