#pragma once
#include <string>

#include "Asset.h"
#include "../Math/LightMath_Cpp/LMath.h"

using namespace Math;

namespace Doom
{
	struct ThreeDModelMesh;
	struct ThreeDModelNode;
	struct ThreeDModelAsset;

	struct ThreeDModelMesh
	{

		std::string Name;

		Vector3** Vertices;
		unsigned int NumOfVertices;
		
		Vector3** TexCoords;
		unsigned int NumOfTexCoords;

		Vector3* Tangents;
		Vector3* BiTangents;

		Vector3* Normals;
		
	};

	struct ThreeDModelNode
	{
		ThreeDModelAsset* ThreeDModelAsset;

		std::string Name;

		ThreeDModelNode* ThreeDModelNodeParent;

		ThreeDModelNode** ThreeDModelNodeChildrens;
		unsigned int NumOfThreeDModelNodeChildrens;

		/// <summary>
		/// each component contain index of ThreeDModelAsset::ThreeDModelMesh 
		/// so use like this->ThreeDModelAsset->ThreeDModelMesh[ThreeDModelMeshes[0]]
		/// </summary>
		ThreeDModelMesh** ThreeDModelMeshes;
		unsigned int NumOfThreeDModelMeshes; 
	};

	struct ThreeDModelAsset : public Asset
	{
		ThreeDModelNode rootNode;

		ThreeDModelMesh** ModelMeshes;
		unsigned int NumOfModelMeshed;



	};
}


