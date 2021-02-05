#include "ThreeDModelAsset.h"

#include <type_traits>
#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"

static_assert(std::is_standard_layout_v<doom::MeshVertexData>);

void doom::ThreeDModelAsset::SendMeshDataToGPU()
{
	this->mNumOfMeshes = this->mNumOfModelMeshAssets;
	if (this->mNumOfMeshes > 0)
	{
		this->mMeshes = new doom::graphics::Mesh[this->mNumOfMeshes];
		for (unsigned int i = 0; i < this->mNumOfMeshes; i++)
		{
			this->mMeshes[i] = this->mModelMeshAssets[i];
		}
	}
	else
	{
		this->mMeshes = nullptr;
	}


	this->mRootMeshNode = new doom::graphics::MeshNode();
	this->CreateNode(this->mRootMeshNode, this->mRootModelNode);
}


void doom::ThreeDModelAsset::ClearMeshData()
{
	delete[] this->mModelMeshAssets;
	delete this->mRootModelNode;

	this->mModelMeshAssets = nullptr;
	this->mRootModelNode = nullptr;
}

void doom::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset)
{
	currentNode->mNumOfMeshes = currentModelNodeAsset->mNumOfModelMeshes;
	if (currentNode->mNumOfMeshes != 0)
	{
		currentNode->mMeshes = new doom::graphics::Mesh*[currentNode->mNumOfMeshes];
		for (unsigned int i = 0; i < currentNode->mNumOfMeshes; i++)
		{
			currentNode->mMeshes[i] = &(this->mMeshes[currentModelNodeAsset->mModelMeshIndexs[i]]);
		}
	}
	else
	{
		currentNode->mMeshes = nullptr;
	}

	currentNode->mNumOfChilds = currentModelNodeAsset->mNumOfThreeDModelNodeChildrens;
	if (currentNode->mNumOfChilds != 0)
	{
		currentNode->mChilds = new doom::graphics::MeshNode[currentNode->mNumOfChilds];
		for (unsigned int i = 0; i < currentNode->mNumOfChilds; i++)
		{
			currentNode->mChilds[i].mParent = currentNode;
			this->CreateNode( &(currentNode->mChilds[i]), &(currentModelNodeAsset->mThreeDModelNodeChildrens[i]) );
		}
	}
	else
	{
		currentNode->mChilds = nullptr;
	}

	
}

void doom::ThreeDModelAsset::OnEndImportInMainThread()
{
	this->SendMeshDataToGPU();
	this->ClearMeshData(); // after send mesh data to gpu, delete all meshes data for memory space
	D_DEBUG_LOG("Cleared Mesh Data", LogType::D_LOG);
}
