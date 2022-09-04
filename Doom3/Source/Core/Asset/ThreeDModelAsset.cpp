#include "ThreeDModelAsset.h"

void dooms::asset::ThreeDModelAsset::CreateMesh()
{
	const INT32 CountOfMeshRawData = MeshRawDataList.size();
	D_ASSERT(CountOfMeshRawData != 0);
	
	MeshList.reserve(CountOfMeshRawData);
	for (UINT32 i = 0; i < CountOfMeshRawData; i++)
	{
		graphics::Mesh* const NewMesh = dooms::CreateDObject<graphics::Mesh>(MeshRawDataList[i]);
		D_ASSERT(IsValid(NewMesh));

		MeshList.push_back(NewMesh);
	}
}


void dooms::asset::ThreeDModelAsset::ClearMeshData()
{
	Root3DModelNode.reset();
	MeshRawDataList.resize(0);
	MeshList.resize(0);
}

void dooms::asset::ThreeDModelAsset::OnEndImportInMainThread_Internal()
{
	CreateMesh();
}

dooms::asset::ThreeDModelAsset::ThreeDModelAsset 
(
	std::vector<graphics::FMeshRawData>&& MeshRawData,
	std::unique_ptr<FMeshNode>&& RootMeshNode
) noexcept
	: Root3DModelNode(std::move(RootMeshNode)), MeshRawDataList{ std::move(MeshRawData) }
{
	CreateMesh();
}


dooms::asset::ThreeDModelAsset::~ThreeDModelAsset()
{
	
}

void dooms::asset::ThreeDModelAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();

	if (Root3DModelNode != nullptr)
	{//check is destroyed
		ClearMeshData();
	}
}

const std::vector<dooms::graphics::Mesh*>& dooms::asset::ThreeDModelAsset::GetMeshes() const
{
	return MeshList;
}

dooms::graphics::Mesh* dooms::asset::ThreeDModelAsset::GetMesh(UINT32 index) 
{
	D_ASSERT(index < GetMeshCount());

	if(index < GetMeshCount())
	{
		//D_ASSERT(mMeshes[index].GetTargetThreeDModelMesh()->mIsValidMesh == true);
		return MeshList[index];
	}
	else
	{
		return nullptr;
	}
	
}

size_t dooms::asset::ThreeDModelAsset::GetMeshCount() const
{
	return MeshList.size();
}

dooms::asset::eAssetType dooms::asset::ThreeDModelAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::THREE_D_MODEL;
}


