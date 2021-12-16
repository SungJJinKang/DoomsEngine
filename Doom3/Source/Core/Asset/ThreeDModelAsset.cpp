#include "ThreeDModelAsset.h"

#include "../Graphics/Buffer/Mesh.h"
#include "../Graphics/Buffer/MeshNode.h"

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

void dooms::asset::ThreeDModelAsset::CreateNode(graphics::MeshNode* currentNode, ThreeDModelNode* currentModelNodeAsset)
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
	ThreeDModelNode* const rootThreeDModelNode
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


dooms::MeshData::MeshData()
	:
	mData(nullptr),
	mVerticeCount(0),
	mVertex(nullptr),
	mTexCoord(nullptr),
	mNormal(nullptr),
	mTangent(nullptr),
	mBitangent(nullptr)
{
}

dooms::MeshData::MeshData(const size_t verticeCount)
	: MeshData()
{
	Allocate(verticeCount);
}

dooms::MeshData::MeshData(const MeshData& meshData)
	:
	mData(nullptr),
	mVerticeCount(0),
	mVertex(nullptr),
	mTexCoord(nullptr),
	mNormal(nullptr),
	mTangent(nullptr),
	mBitangent(nullptr)
{
	Allocate(meshData.mVerticeCount);

	std::memcpy(mData, meshData.mData, (sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)) * mVerticeCount);
}

dooms::MeshData::MeshData(MeshData&& meshData) noexcept
	:
	mData(meshData.mData),
	mVerticeCount(meshData.mVerticeCount),
	mVertex(meshData.mVertex),
	mTexCoord(meshData.mTexCoord),
	mNormal(meshData.mNormal),
	mTangent(meshData.mTangent),
	mBitangent(meshData.mBitangent)
{
	meshData.mData = nullptr;
	meshData.mVerticeCount = 0;
	meshData.mVertex = nullptr;
	meshData.mTexCoord = nullptr;
	meshData.mNormal = nullptr;
	meshData.mTangent = nullptr;
	meshData.mBitangent = nullptr;
}

dooms::MeshData& dooms::MeshData::operator=(const MeshData& meshData)
{
	if(mVerticeCount == meshData.mVerticeCount)
	{
		std::memcpy(mData, meshData.mData, (sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)) * mVerticeCount);
	}
	else
	{
		Free();

		Allocate(meshData.mVerticeCount);

		std::memcpy(mData, meshData.mData, (sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)) * mVerticeCount);
	}

	return *this;
}

dooms::MeshData& dooms::MeshData::operator=(MeshData&& meshData) noexcept
{
	Free();

	mData = meshData.mData;
	mVerticeCount = meshData.mVerticeCount;
	mVertex = meshData.mVertex;
	mTexCoord = meshData.mTexCoord;
	mNormal = meshData.mNormal;
	mTangent = meshData.mTangent;
	mBitangent = meshData.mBitangent;

	meshData.mData = nullptr;
	meshData.mVerticeCount = 0;
	meshData.mVertex = nullptr;
	meshData.mTexCoord = nullptr;
	meshData.mNormal = nullptr;
	meshData.mTangent = nullptr;
	meshData.mBitangent = nullptr;

	return *this;
}

dooms::MeshData::~MeshData()
{
	Free();
}

void dooms::MeshData::Allocate(const size_t verticeCount)
{
	D_ASSERT(mData == nullptr);
	if(verticeCount != 0)
	{
		mData = reinterpret_cast<char*>(std::malloc((sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)) * verticeCount));
		mVerticeCount = verticeCount;

		mVertex = reinterpret_cast<Vector3*>(mData);
		mTexCoord = reinterpret_cast<Vector3*>((char*)mVertex + sizeof(Vector3) * verticeCount);
		mNormal = reinterpret_cast<Vector3*>((char*)mTexCoord + sizeof(Vector3) * verticeCount);
		mTangent = reinterpret_cast<Vector3*>((char*)mNormal + sizeof(Vector3) * verticeCount);
		mBitangent = reinterpret_cast<Vector3*>((char*)mTangent + sizeof(Vector3) * verticeCount);
	}
	
}

size_t dooms::MeshData::GetAllocatedDataSize() const
{
	return (sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3)) * mVerticeCount;
}

void dooms::MeshData::Free()
{
	if (mData != nullptr)
	{
		free(mData);
	}

	mVerticeCount = 0;
	mVertex = nullptr;
	mTexCoord = nullptr;
	mNormal = nullptr;
	mTangent = nullptr;
	mBitangent = nullptr;
}
