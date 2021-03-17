#pragma once
#include <string>

#include "Base_Asset.h"

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"
#include "../Graphics/ePrimitiveType.h"
#include <optional>
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

using namespace math;




namespace doom
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
		unsigned int mNumIndices;
		unsigned int* mIndices;
	};
	*/

	
	struct ThreeDModelMesh
	{
		std::string mName;

		ePrimitiveType mPrimitiveType;

		bool bHasIndices;
		unsigned int mNumOfIndices;
		/// <summary>
		/// mMeshIndices count is mNumOfIndiecs
		/// </summary>
		std::unique_ptr<unsigned int[]> mMeshIndices;

		unsigned int mNumOfVertexs;
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
		doom::asset::ThreeDModelAsset* mThreeDModelAsset;

		std::string mName;

		/// <summary>
		/// don't clear this
		/// </summary>
		ThreeDModelNode* mThreeDModelNodeParent; // why don't use unique_ptr at here, Parent node will be deleted later

		std::unique_ptr<ThreeDModelNode[]> mThreeDModelNodeChildrens;
		unsigned int mNumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like this->ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		std::unique_ptr<unsigned int[]> mModelMeshIndexs;
		unsigned int mNumOfModelMeshes;

		ThreeDModelNode() = default;
		ThreeDModelNode(const ThreeDModelNode&) = delete;
		ThreeDModelNode(ThreeDModelNode&&) noexcept = default;
		ThreeDModelNode& operator=(const ThreeDModelNode&) = delete;
		ThreeDModelNode& operator=(ThreeDModelNode&&) noexcept = default;
		~ThreeDModelNode() = default;
	};


	namespace asset
	{
		class ThreeDModelAsset : public Asset
		{
			//friend class std::optional<ThreeDModelAsset>;

			friend class ::doom::assetimporter::ImportedAssetPort<eAssetType::THREE_D_MODEL>;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

		private:
			std::unique_ptr<ThreeDModelNode> mRootModelNode{};

			std::unique_ptr<ThreeDModelMesh[]> mModelMeshAssets{};
			unsigned int mNumOfModelMeshAssets{};

			///////////

			std::unique_ptr<graphics::MeshNode> mRootMeshNode{};
			std::vector<graphics::Mesh> mMeshes{};

			unsigned int mNumOfMeshes{};

			/// <summary>
			/// Send Meshdata to GPU
			/// GPU Buffer
			/// </summary>
			void SendMeshDataToGPU();

			void ClearMeshData();
			void CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset);
			void OnEndImportInMainThread_Internal() final;


		public:
			/// <summary>
			/// why const? to protect asset data
			/// </summary>
			/// <returns></returns>
			const std::vector<graphics::Mesh>& GetMeshes() const;
			graphics::Mesh* GetMesh(unsigned int index);
			size_t GetMeshCount() const;

			ThreeDModelAsset() = default;
			ThreeDModelAsset(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset(ThreeDModelAsset&& threeDAsset) noexcept = default;
			ThreeDModelAsset& operator=(const ThreeDModelAsset&) = delete;
			ThreeDModelAsset& operator=(ThreeDModelAsset&& threeDAsset) noexcept = default;
			~ThreeDModelAsset();

		};

		template <> struct Asset::asset_type<eAssetType::THREE_D_MODEL> { using type = typename ThreeDModelAsset; };
	}
}


