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
	/// </summary>
	struct MeshVertexData
	{
		Vector3 mVertex;
		Vector2 mTexCoord; //support only one channel
		Vector3 mNormal;
		Vector3 mTangent;
		Vector3 mBitangent;
	};
#define VERTEX_DATA_SIZE 16

	struct ThreeDModelMesh
	{
		std::string mName;

		unsigned int mNumOfVertices;
		MeshVertexData mMeshVertexData;
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


