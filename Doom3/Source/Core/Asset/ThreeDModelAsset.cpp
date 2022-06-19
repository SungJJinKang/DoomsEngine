#include "ThreeDModelAsset.h"


//static_assert(std::is_standard_layout_v<dooms::MeshData>);

void dooms::asset::ThreeDModelAsset::SendMeshDataToGPU()
{
	mNumOfMeshes = mModelMeshAssets.size();
	D_ASSERT(mNumOfMeshes != 0);
	if (mNumOfMeshes > 0)
	{
		mMeshes.reserve(mNumOfMeshes);
		for (UINT32 i = 0; i < mNumOfMeshes; i++)
		{
			mMeshes.emplace_back(mModelMeshAssets[i]);
		}
	}

	mRootMeshNode = dooms::CreateDObject<dooms::graphics::MeshNode>();
	CreateNode(mRootMeshNode, mRootModelNode);
}


void dooms::asset::ThreeDModelAsset::ClearMeshData()
{
	mModelMeshAssets.resize(0);
	mRootModelNode->SetIsPendingKill();

}

void dooms::asset::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, FMeshNode* currentModelNodeAsset)
{
	const size_t indiceCount = currentModelNodeAsset->mModelMeshIndexs.size();
	if (indiceCount != 0)
	{
		currentNode->mMeshes.resize(indiceCount);
		for (size_t i = 0; i < indiceCount ; i++)
		{
			currentNode->mMeshes[i] = &(mMeshes[currentModelNodeAsset->mModelMeshIndexs[i]]);
		}
	}
	else
	{
		currentNode->mMeshes.resize(0);
	}

	const size_t nodeChildrenCount = currentModelNodeAsset->mThreeDModelNodeChildrens.size();
	if (nodeChildrenCount != 0)
	{
		currentNode->mChilds.resize(nodeChildrenCount);
		for (size_t i = 0; i < nodeChildrenCount ; i++)
		{
			currentNode->mChilds[i].mParent = currentNode;
			CreateNode( &(currentNode->mChilds[i]), &(currentModelNodeAsset->mThreeDModelNodeChildrens[i]) );
		}
	}
	else
	{
		currentNode->mChilds.resize(0);
	}

	
}

void dooms::asset::ThreeDModelAsset::OnEndImportInMainThread_Internal()
{
	SendMeshDataToGPU();
}

dooms::asset::ThreeDModelAsset::ThreeDModelAsset 
(
	std::vector<ThreeDModelMesh>&& threeDModelMeses,
	FMeshNode* const rootThreeDModelNode
) noexcept
	: mRootModelNode(rootThreeDModelNode), mModelMeshAssets{ std::move(threeDModelMeses) }
{
	SendMeshDataToGPU();
}


dooms::asset::ThreeDModelAsset::~ThreeDModelAsset()
{
	
}

void dooms::asset::ThreeDModelAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();

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
	D_ASSERT(index < GetMeshCount());

	if(index < GetMeshCount())
	{
		//D_ASSERT(mMeshes[index].GetTargetThreeDModelMesh()->mIsValidMesh == true);
		return &mMeshes[index];
	}
	else
	{
		return nullptr;
	}
	
}

size_t dooms::asset::ThreeDModelAsset::GetMeshCount() const
{
	return mMeshes.size();
}

dooms::asset::eAssetType dooms::asset::ThreeDModelAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::THREE_D_MODEL;
}


