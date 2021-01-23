#include "AssetImporterWorker_Three_D_Model.h"

#include "AssetApiImporter.h"

using namespace Doom;
using namespace AssetImporter;


void Doom::AssetImporter::SetThreeDModelNodesData(ThreeDModelNode* currentNode, aiNode* currentAssimpNode, ThreeDModelNode* parentNode, ThreeDModelAsset& modelAsset, const aiScene* assimpScene)
{
	currentNode->ThreeDModelNodeParent = parentNode;
	currentNode->ThreeDModelAsset = &modelAsset;
	currentNode->Name = currentAssimpNode->mName.C_Str();
	currentNode->NumOfThreeDModelMeshes = currentAssimpNode->mNumMeshes;

	currentNode->ThreeDModelMeshes = new ThreeDModelMesh * [currentAssimpNode->mNumMeshes];
	for (unsigned int meshIndex = 0; meshIndex < currentAssimpNode->mNumMeshes; meshIndex++)
	{
		currentNode->ThreeDModelMeshes[meshIndex] = modelAsset.ModelMeshes[currentAssimpNode->mMeshes[meshIndex]];
	}

	currentNode->NumOfThreeDModelNodeChildrens = currentAssimpNode->mNumChildren;
	currentNode->ThreeDModelNodeChildrens = new ThreeDModelNode * [currentAssimpNode->mNumChildren];
	for (unsigned int childrenIndex = 0; childrenIndex < currentAssimpNode->mNumChildren; childrenIndex++)
	{
		currentNode->ThreeDModelNodeChildrens[childrenIndex] = new ThreeDModelNode();
		Doom::AssetImporter::SetThreeDModelNodesData(currentNode->ThreeDModelNodeChildrens[childrenIndex], currentAssimpNode->mChildren[childrenIndex], currentNode, modelAsset, assimpScene);
	}
}


