#include "ThreeDModelAsset.h"

#include <type_traits>
#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"

static_assert(std::is_standard_layout_v<doom::MeshVertexData>);

void doom::asset::ThreeDModelAsset::SendMeshDataToGPU()
{
	mNumOfMeshes = mNumOfModelMeshAssets;
	if (mNumOfMeshes > 0)
	{
		mMeshes.reserve(mNumOfMeshes);
		for (unsigned int i = 0; i < mNumOfMeshes; i++)
		{
			mMeshes.emplace_back(mModelMeshAssets[i]);
		}
	}
	else
	{
		//mMeshes = nullptr;
	}


	mRootMeshNode = std::make_unique<doom::graphics::MeshNode>();
	CreateNode(mRootMeshNode.get(), mRootModelNode.get());
}


void doom::asset::ThreeDModelAsset::ClearMeshData()
{
	mModelMeshAssets.reset();
	mRootModelNode.reset();

}

void doom::asset::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset)
{
	currentNode->mNumOfMeshes = currentModelNodeAsset->mNumOfModelMeshes;
	if (currentNode->mNumOfMeshes != 0)
	{
		currentNode->mMeshes = std::make_unique< doom::graphics::Mesh* []>(currentNode->mNumOfMeshes);
		for (unsigned int i = 0; i < currentNode->mNumOfMeshes; i++)
		{
			currentNode->mMeshes[i] = &(mMeshes[currentModelNodeAsset->mModelMeshIndexs[i]]);
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
			CreateNode( &(currentNode->mChilds[i]), &(currentModelNodeAsset->mThreeDModelNodeChildrens[i]) );
		}
	}
	else
	{
		currentNode->mChilds = nullptr;
	}

	
}

void doom::asset::ThreeDModelAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING("Postprocess 3D Model", eProfileLayers::Rendering);
	SendMeshDataToGPU();
	//ClearMeshData(); // after send mesh data to gpu, delete all meshes data for memory space
	D_END_PROFILING("Postprocess 3D Model");
}


doom::asset::ThreeDModelAsset::~ThreeDModelAsset()
{
	if (mRootModelNode != nullptr)
	{//check is destroyed
		ClearMeshData();
	}
}

const std::vector<doom::graphics::Mesh>& doom::asset::ThreeDModelAsset::GetMeshes() const
{
	return mMeshes;
}

doom::graphics::Mesh* doom::asset::ThreeDModelAsset::GetMesh(unsigned int index) 
{
	D_ASSERT(index >= 0 && index < GetMeshCount());
	return &(mMeshes[index]);
}

size_t doom::asset::ThreeDModelAsset::GetMeshCount() const
{
	return mMeshes.size();
}

