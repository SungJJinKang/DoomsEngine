#pragma once
#include <string>

#include "Base_Asset.h"

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Graphics/Buffer/Mesh.h"
#include "ePrimitiveType.h"

using namespace math;




namespace doom
{
	struct ThreeDModelMesh;
	struct ThreeDModelNode;
	class ThreeDModelAsset;

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
		unsigned int* mMeshIndices;

		unsigned int mNumOfVertexs;
		/// <summary>
		/// mMeshVertexDatas count is mNumOfVertices
		/// Vertices data is packed
		/// 
		/// ( O ) Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent | Vertex TexCoord Normal Tangent Bitangent
		/// ( X ) Vertex Vertex Vertex | TexCoord TexCoord TexCoord | Normal Normal Normal | Tangent Tangent Tangent | Bitangent Bitangent Bitangent
		/// </summary>
		MeshVertexData* mMeshVertexDatas;

		~ThreeDModelMesh()
		{
			delete[] mMeshIndices;
			delete[] mMeshVertexDatas;
		}
	};

	struct ThreeDModelNode
	{ 
		/// <summary>
		/// don't clear this
		/// </summary>
		doom::ThreeDModelAsset* mThreeDModelAsset;

		std::string mName;

		/// <summary>
		/// don't clear this
		/// </summary>
		ThreeDModelNode* mThreeDModelNodeParent;

		ThreeDModelNode* mThreeDModelNodeChildrens;
		unsigned int mNumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like this->ThreeDModelAsset->mModelMeshAssets[mModelMeshIndexs[0]]
		/// </summary>
		unsigned int* mModelMeshIndexs;
		unsigned int mNumOfModelMeshes;

		~ThreeDModelNode()
		{
			if (mNumOfThreeDModelNodeChildrens != 0)
			{
				delete[] mThreeDModelNodeChildrens;
			}
			/*
			for (unsigned int i = 0; i < mNumOfThreeDModelNodeChildrens; i++)
			{
				delete 
			}
			*/

			delete[] mModelMeshIndexs;
		}
	};

	namespace graphics
	{
		class Mesh;
		struct MeshNode;
	}

	namespace assetimporter
	{
		template <Asset::eAssetType assetType>
		class AssetImporterWorker;
	}
	


	class ThreeDModelAsset : public Asset
	{
		template<Asset::eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

		friend class assetimporter::AssetImporterWorker<Asset::eAssetType::THREE_D_MODEL>;
	private:
		ThreeDModelNode* mRootModelNode{};

		ThreeDModelMesh* mModelMeshAssets{};
		unsigned int mNumOfModelMeshAssets;

		///////////

		graphics::MeshNode* mRootMeshNode{};
		std::vector<graphics::Mesh> mMeshes{};
		
		unsigned int mNumOfMeshes;

		/// <summary>
		/// Send Meshdata to GPU
		/// GPU Buffer
		/// </summary>
		void SendMeshDataToGPU();

		void ClearMeshData();
		void CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset);
		void OnEndImportInMainThread() final;
		
	public:
		const std::vector<graphics::Mesh>& GetMeshes();
	};

	template <> struct Asset::asset_type<Asset::eAssetType::THREE_D_MODEL> { using type = typename ThreeDModelAsset; };
}


