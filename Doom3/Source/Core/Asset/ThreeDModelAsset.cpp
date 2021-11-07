#include "ThreeDModelAsset.h"

#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"

//static_assert(std::is_standard_layout_v<dooms::MeshVertexData>);

void dooms::asset::ThreeDModelAsset::SendMeshDataToGPU()
{
	mNumOfMeshes = mNumOfModelMeshAssets;
	if (mNumOfMeshes > 0)
	{
		mMeshes.reserve(mNumOfMeshes);
		for (UINT32 i = 0; i < mNumOfMeshes; i++)
		{
			mMeshes.emplace_back(mModelMeshAssets[i]);
		}
	}
	else
	{
		//mMeshes = nullptr;
	}


	mRootMeshNode = std::make_unique<dooms::graphics::MeshNode>();
	CreateNode(mRootMeshNode.get(), mRootModelNode.get());
}


void dooms::asset::ThreeDModelAsset::ClearMeshData()
{
	mModelMeshAssets.reset();
	mRootModelNode.reset();

}

void dooms::asset::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset)
{
	currentNode->mNumOfMeshes = currentModelNodeAsset->mNumOfModelMeshes;
	if (currentNode->mNumOfMeshes != 0)
	{
		currentNode->mMeshes = std::make_unique< dooms::graphics::Mesh* []>(currentNode->mNumOfMeshes);
		for (UINT32 i = 0; i < currentNode->mNumOfMeshes; i++)
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
		currentNode->mChilds = std::make_unique< dooms::graphics::MeshNode[]>(currentNode->mNumOfChilds);
		for (UINT32 i = 0; i < currentNode->mNumOfChilds; i++)
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

void dooms::asset::ThreeDModelAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Postprocess_3D_Model, eProfileLayers::Rendering);
	SendMeshDataToGPU();
	//ClearMeshData(); // after send mesh data to gpu, delete all meshes data for memory space
	D_END_PROFILING(Postprocess_3D_Model);
}


dooms::asset::ThreeDModelAsset::~ThreeDModelAsset()
{
	if (mRootModelNode != nullptr)
	{//check is destroyed
		ClearMeshData();
	}
}

const std::vector<dooms::graphics::Mesh>& dooms::asset::ThreeDModelAsset::GetMeshes() const
{
	return mMeshes;
}

dooms::graphics::Mesh* dooms::asset::ThreeDModelAsset::GetMesh(UINT32 index) 
{
	D_ASSERT(index >= 0 && index < GetMeshCount());
	return &(mMeshes[index]);
}

size_t dooms::asset::ThreeDModelAsset::GetMeshCount() const
{
	return mMeshes.size();
}

dooms::asset::eAssetType dooms::asset::ThreeDModelAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::THREE_D_MODEL;
}

