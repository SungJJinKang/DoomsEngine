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
		this->mMeshes.reserve(this->mNumOfMeshes);
		for (unsigned int i = 0; i < this->mNumOfMeshes; i++)
		{
			this->mMeshes.emplace_back(this->mModelMeshAssets[i]);
		}
	}
	else
	{
		//this->mMeshes = nullptr;
	}


	this->mRootMeshNode = std::make_unique<doom::graphics::MeshNode>();
	this->CreateNode(this->mRootMeshNode.get(), this->mRootModelNode.get());
}


void doom::ThreeDModelAsset::ClearMeshData()
{
	this->mModelMeshAssets.reset();
	this->mRootModelNode.reset();

}

void doom::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset)
{
	currentNode->mNumOfMeshes = currentModelNodeAsset->mNumOfModelMeshes;
	if (currentNode->mNumOfMeshes != 0)
	{
		currentNode->mMeshes = std::make_unique< doom::graphics::Mesh* []>(currentNode->mNumOfMeshes);
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
		currentNode->mChilds = std::make_unique< doom::graphics::MeshNode[]>(currentNode->mNumOfChilds);
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
	D_DEBUG_LOG("Cleared Mesh Data", eLogType::D_LOG);
}


doom::ThreeDModelAsset::~ThreeDModelAsset()
{
	if (this->mRootModelNode != nullptr)
	{//check is destroyed
		this->ClearMeshData();
	}
}

const std::vector<doom::graphics::Mesh>& doom::ThreeDModelAsset::GetMeshes() 
{
	return this->mMeshes;
}

doom::graphics::Mesh& doom::ThreeDModelAsset::GetMesh(unsigned int index) 
{
	D_ASSERT(index >= 0 && index < GetMeshCount());
	return this->mMeshes[index];
}

size_t doom::ThreeDModelAsset::GetMeshCount() const
{
	return this->mMeshes.size();
}

