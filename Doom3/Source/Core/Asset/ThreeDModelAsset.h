#pragma once
#include <string>

#include "Asset.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Rendering/Buffer/Mesh.h>
#include <Rendering/Buffer/MeshNode.h>
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

using namespace math;


#include "ThreeDModelAsset.reflection.h"
D_NAMESPACE(dooms)
namespace dooms
{
	class ThreeDModelMesh;
	class ThreeDModelNode;

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
	struct DOOM_API MeshData
	{
	public:
		D_PROPERTY()
		UINT64 mVerticeCount;

		D_PROPERTY()
		char* mData;

		D_PROPERTY()
		Vector3* mVertex;

		D_PROPERTY()
		Vector3* mTexCoord; //support only one channel

		D_PROPERTY()
		Vector3* mNormal;

		D_PROPERTY()
		Vector3* mTangent;

		D_PROPERTY()
		Vector3* mBitangent;

		MeshData();
		MeshData(const size_t verticeCount);
		MeshData(const MeshData&);
		MeshData(MeshData&&) noexcept;
		MeshData& operator=(const MeshData&);
		MeshData& operator=(MeshData&&) noexcept;
		~MeshData();

		void Allocate(const size_t verticeCount);
		unsigned long long GetAllocatedDataSize() const;
		void Free();
	};
	D_REFLECTION_TYPE(dooms::MeshVertexData)

	/*
	struct MeshFaceData
	{
		UINT32 mNumIndices;
		UINT32* mIndices;
	};
	*/

	
	class DOOM_API D_CLASS ThreeDModelMesh : public DObject
	{
		GENERATE_BODY_ThreeDModelMesh()

	public:

		D_PROPERTY()
		bool mIsValidMesh;

		D_PROPERTY()
		std::string mName;

		D_PROPERTY()
		graphics::GraphicsAPI::ePrimitiveType mPrimitiveType;

		D_PROPERTY()
		bool bHasIndices;
		
		/// <summary>
		/// mMeshIndices count is mNumOfIndiecs
		/// </summary>
		D_PROPERTY()
		std::vector<UINT32> mMeshIndices;
		
		/// <summary>
		/// mMeshDatas count is mNumOfVertices
		/// Vertices data is packed
		/// 
		/// ( O ) Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent
		/// ( X ) Vertex Vertex Vertex | TexCoord TexCoord TexCoord | Normal Normal Normal | Tangent Tangent Tangent | Bitangent Bitangent Bitangent
		/// </summary>
		D_PROPERTY()
		MeshData mMeshDatas;

		D_PROPERTY()
		UINT32 mVerticeStride;

		D_PROPERTY()
		UINT32 mVertexArrayFlag;

		D_PROPERTY()
		physics::AABB3D mAABB3D{nullptr};
		D_PROPERTY()
		physics::Sphere mSphere{nullptr};

		ThreeDModelMesh() = default;
		ThreeDModelMesh(int*) : mAABB3D{nullptr}, mSphere{nullptr}
		{}
		ThreeDModelMesh(const ThreeDModelMesh&) = default;
		ThreeDModelMesh(ThreeDModelMesh&&) noexcept = default;
		ThreeDModelMesh& operator=(const ThreeDModelMesh&) = default;
		ThreeDModelMesh& operator=(ThreeDModelMesh&&) noexcept = default;
		~ThreeDModelMesh() = default;
	};

	class DOOM_API D_CLASS ThreeDModelNode : public DObject
	{
		GENERATE_BODY_ThreeDModelNode()

	public:

		D_PROPERTY()
		std::string mName;

		/// <summary>
		/// don't clear this
		/// </summary>
		D_PROPERTY()
		ThreeDModelNode* mThreeDModelNodeParent = nullptr; // Parent node will be deleted later

		D_PROPERTY()
		std::vector<ThreeDModelNode> mThreeDModelNodeChildrens;
		
		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		D_PROPERTY()
		std::vector<UINT32> mModelMeshIndexs;

		ThreeDModelNode() = default;
		ThreeDModelNode(int*)
			: mThreeDModelNodeParent{ nullptr } {}
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
			ThreeDModelNode* mRootModelNode{};

			D_PROPERTY()
			std::vector<ThreeDModelMesh> mModelMeshAssets;

			///////////

			D_PROPERTY()
			graphics::MeshNode* mRootMeshNode{nullptr};

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
			void CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset);
			void OnEndImportInMainThread_Internal() final;


		public:
			
			ThreeDModelAsset() = default;
			ThreeDModelAsset(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset
			(
				std::vector<ThreeDModelMesh>&& threeDModelMeses, 
				ThreeDModelNode* const rootThreeDModelNode
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


