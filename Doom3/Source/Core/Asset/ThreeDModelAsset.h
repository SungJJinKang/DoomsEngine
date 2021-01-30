#pragma once
#include <string>

#include "Base_Asset.h"

#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"

using namespace Math;

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

	enum class ePrimitiveType
	{
		POINT = 0x1,
		LINE = 0x2,
		TRIANGLE = 0x4,
		POLYGON = 0x8
	};

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
	};

	struct ThreeDModelNode
	{
		doom::ThreeDModelAsset* mThreeDModelAsset;

		std::string mName;

		ThreeDModelNode* mThreeDModelNodeParent;

		ThreeDModelNode* mThreeDModelNodeChildrens;
		unsigned int mNumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like this->ThreeDModelAsset->ThreeDModelMesh[ThreeDmModelMeshes[0]]
		/// </summary>
		ThreeDModelMesh** mThreeDmModelMeshes;
		unsigned int mNumOfThreeDmModelMeshes; 
	};

	class ThreeDModelAsset : public Asset
	{
	public:
		ThreeDModelNode mRootNode;

		ThreeDModelMesh* mModelMeshes;
		unsigned int mNumOfModelMesh;



	};

	template <> struct Asset::asset_type<Asset::eAssetType::THREE_D_MODEL> { using type = typename ThreeDModelAsset; };
}


