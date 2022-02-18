#include "Mesh.h"


#include "../Asset/ThreeDModelAsset.h"
#include "eVertexArrayFlag.h"
#include "Matrix3x3.h"

UINT64 dooms::graphics::Mesh::BOUND_VERTEX_ARRAY_ID{(UINT64)-1};
UINT64 dooms::graphics::Mesh::BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT]{ (UINT64)-1 };
UINT64 dooms::graphics::Mesh::BOUND_INDEX_BUFFER_ID{ (UINT64)-1 };

dooms::graphics::Mesh::Mesh()
	:
	Buffer(),
	mVertexDataBuffer{},
	mVertexArrayObjectID{},
	mElementBufferObjectID{},
	mTargetThreeDModelMesh{nullptr},
	mNumOfVertices{ 0 },
	mNumOfIndices{ 0 },
	mPrimitiveType{ GraphicsAPI::ePrimitiveType::NONE },
	mVertexBufferLayoutCount(),
	mVertexBufferLayouts()
{

}

dooms::graphics::Mesh::Mesh
(
	const UINT64 dataComponentCount,
	const UINT64 vertexCount,
	const void* data, 
	GraphicsAPI::ePrimitiveType primitiveType,
	UINT32 vertexArrayFlag,
	const UINT32* const indices,
	const UINT64 indiceCount,
	const bool dynamicWrite
)
	:
	Buffer(),
	mVertexDataBuffer{},
	mVertexArrayObjectID{},
	mElementBufferObjectID{},
	mTargetThreeDModelMesh{ nullptr },
	mNumOfVertices{ 0 },
	mNumOfIndices{ 0 },
	mPrimitiveType{ GraphicsAPI::ePrimitiveType::NONE },
	mVertexBufferLayoutCount(),
	mVertexBufferLayouts()
{
	CreateBufferObject(dataComponentCount, vertexCount, data, primitiveType, vertexArrayFlag, indices, indiceCount, dynamicWrite);
}


dooms::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh)
	:
	Buffer(),
	mVertexDataBuffer{},
	mVertexArrayObjectID{},
	mElementBufferObjectID{},
	mTargetThreeDModelMesh{ nullptr },
	mNumOfVertices{ 0 },
	mNumOfIndices{ 0 },
	mPrimitiveType{ GraphicsAPI::ePrimitiveType::NONE },
	mVertexBufferLayoutCount(),
	mVertexBufferLayouts()
{
	CreateBufferObjectFromModelMesh(threeDModelMesh);
}

dooms::graphics::Mesh::~Mesh()
{
	DeleteBuffers();
	
}

void dooms::graphics::Mesh::OnSetPendingKill()
{
	Buffer::OnSetPendingKill();

	DeleteBuffers();
}


void dooms::graphics::Mesh::DeleteBuffers()
{
	if (mVertexDataBuffer.IsValid())
	{
		GraphicsAPI::DestroyBuffer(mVertexDataBuffer);
		mVertexDataBuffer.Reset();
	}

	if (mElementBufferObjectID.IsValid())
	{
		GraphicsAPI::DestroyBuffer( mElementBufferObjectID );
		mElementBufferObjectID.Reset();
	}

	if (mVertexArrayObjectID.IsValid())
	{
		GraphicsAPI::DestroyVertexArrayObject(mVertexArrayObjectID);
		mVertexArrayObjectID.Reset();
	}
}

dooms::graphics::Mesh& dooms::graphics::Mesh::operator=(const ThreeDModelMesh& threeDModelMesh)
{
	DeleteBuffers();
	
	CreateBufferObjectFromModelMesh(threeDModelMesh);
	return *this;
}


const dooms::ThreeDModelMesh* dooms::graphics::Mesh::GetTargetThreeDModelMesh() const
{
	return mTargetThreeDModelMesh;
}

void dooms::graphics::Mesh::CreateBufferObject
(
	const UINT64 dataComponentCount,
	const UINT64 vertexCount,
	const void* data, 
	GraphicsAPI::ePrimitiveType primitiveType,
	UINT32 vertexArrayFlag,
	const UINT32* const indices,
	const UINT64 indiceCount,
	const bool dynamicWrite
) noexcept
{
	D_ASSERT(IsBufferGenerated() == false);
	if (IsBufferGenerated() == false)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			CreateVertexArrayObjectIfNotExist();
		}

		const UINT32 stride = Mesh::GetStride(vertexArrayFlag);
		mTotalStride = stride;

		BindVertexArrayObject(); // bind vertex array buffer

		D_DEBUG_LOG(eLogType::D_LOG, "%f", sizeof(FLOAT32) * dataComponentCount);
		mVertexDataBuffer = GraphicsAPI::CreateBufferObject
		(
			GraphicsAPI::eBufferTarget::ARRAY_BUFFER, 
			static_cast<unsigned long long>(sizeof(FLOAT32) * dataComponentCount), 
			data,
			dynamicWrite
		);
		BindVertexBufferObject();
		
#pragma warning( disable : 4312 )

		D_ASSERT(((vertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((vertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));

		UINT64 offset = 0;
		UINT32 vertexLayoutCount = 0;
		UINT32 layoutIndex = 0;
		if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mVertex
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 2, sizeof(math::Vector2), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector2);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector2);
		}

		if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mVertex
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector3);
		}

		if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mTexCoord
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector2);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mNormal)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mNormal
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector3);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mTangent)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mTangent
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector3);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
		{
			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mBitangent
				GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;
			layoutIndex++;

			offset += vertexCount * sizeof(math::Vector3);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mTBN)
		{
			for(size_t i = 0 ; i < 3 ; i++)
			{
				//const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mBitangent - threeDModelMesh.mMeshDatas.mData);
				if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
				{
					//mBitangent
					GraphicsAPI::EnableVertexAttributeArrayIndex(layoutIndex);
					GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, sizeof(math::Vector3), offset);
				}

				mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
				mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
				vertexLayoutCount++;
				layoutIndex++;

				offset += vertexCount * sizeof(math::Vector3);
			}
			
		}

		mVertexBufferLayoutCount = vertexLayoutCount;

#pragma warning( disable : 4244 )
		mNumOfVertices = vertexCount;
		mNumOfIndices = indiceCount;
		if (mNumOfIndices > 0)
		{
			mElementBufferObjectID = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, mNumOfIndices * sizeof(UINT32), NULL, false);
			GraphicsAPI::UpdateDataToBuffer(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, mNumOfIndices * sizeof(UINT32), reinterpret_cast<const void*>(indices));
		}

		mPrimitiveType = primitiveType;
		mVertexArrayFlag = vertexArrayFlag;

	}
}

/*
void dooms::graphics::Mesh::UpdateVertexData
(
	const long long int dataSize,
	const void* data,
	const long long int offsetInByte
) const noexcept
{
	D_ASSERT(mVertexDataBuffer.IsValid());
	D_ASSERT_LOG()
	
	BindVertexBufferObject();
	GraphicsAPI::UpdateDataToBuffer(mVertexDataBuffer, GraphicsAPI::ARRAY_BUFFER, offsetInByte, dataSize, data);
}
*/


void dooms::graphics::Mesh::CreateVertexArrayObjectIfNotExist()
{
	D_ASSERT(graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL);
	
	if (mVertexArrayObjectID.IsValid() == false)
	{
		mVertexArrayObjectID = GraphicsAPI::CreateVertexArrayObject();
	}
	BindVertexArrayObject(); // bind vertex array buffer first
}

void dooms::graphics::Mesh::CreateBufferObjectFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	D_ASSERT(IsBufferGenerated() == false);
	if (IsBufferGenerated() == false)
	{
		if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			CreateVertexArrayObjectIfNotExist();
		}

		mTotalStride = GetStride(mVertexArrayFlag);

		BindVertexArrayObject(); // bind vertex array buffer

		mVertexDataBuffer = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ARRAY_BUFFER, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), threeDModelMesh.mMeshDatas.mData, false);
		D_ASSERT(mVertexDataBuffer.IsValid());
		//GraphicsAPI::UpdateDataToBuffer(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, 0, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), reinterpret_cast<const void*>(threeDModelMesh.mMeshDatas.mData));

		UINT32 vertexLayoutCount = 0;
		UINT32 layoutIndex = 0;

		//mVertex
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::VertexVector3)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mVertex));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mVertex - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(0);
				GraphicsAPI::EnableVertexAttributeArrayIndex(0); GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
			layoutIndex++;
		}

		//mTexCoord
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::TexCoord)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mTexCoord));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTexCoord - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(1);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
			layoutIndex++;
		}

		//mNormal
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mNormal)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mNormal));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mNormal - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(2);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
			layoutIndex++;
		}

		//mTangent
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mTangent)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mTangent));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTangent - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(3);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
			layoutIndex++;
		}

		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mBitangent)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mBitangent));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mBitangent - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(4);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, layoutIndex, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
			layoutIndex++;
		}
		
		mVertexBufferLayoutCount = vertexLayoutCount;
		mNumOfVertices = threeDModelMesh.mMeshDatas.mVerticeCount;

		// only fill the index buffer if the index array is non-empty.
		mNumOfIndices = 0;
		if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mMeshIndices.size() > 0)
		{
			mElementBufferObjectID = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), NULL, false);
			GraphicsAPI::UpdateDataToBuffer(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), reinterpret_cast<const void*>(threeDModelMesh.mMeshIndices.data()));
			mNumOfIndices = threeDModelMesh.mMeshIndices.size();
		}

		mPrimitiveType = threeDModelMesh.mPrimitiveType;

		mAABB3D = threeDModelMesh.mAABB3D;
		mSphere = threeDModelMesh.mSphere;

		mVertexArrayFlag = threeDModelMesh.mVertexArrayFlag;

		D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

		mTargetThreeDModelMesh = &threeDModelMesh;
	}
}

constexpr UINT32 dooms::graphics::Mesh::GetStride(const UINT32 vertexArrayFlag)
{
	UINT32 offset = 0;

	if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		//mVertex
		offset += sizeof(math::Vector2);
	}

	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		offset += sizeof(math::Vector3);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		offset += sizeof(math::Vector3);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		offset += sizeof(math::Vector3);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		offset += sizeof(math::Vector3);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		offset += sizeof(math::Vector3);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTBN)
	{
		//mBitangent
		offset += sizeof(math::Matrix3x3);
	}

	return offset;
}



bool dooms::graphics::Mesh::IsBufferGenerated() const
{
	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return mVertexDataBuffer.IsValid() && mVertexArrayObjectID.IsValid();
	}
	else if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		return mVertexDataBuffer.IsValid();
	}
	else
	{
		NEVER_HAPPEN;
		return false;
	}
}

/*
void dooms::graphics::Mesh::UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount)
{
	D_ASSERT(IsBufferGenerated() == true);

	if (graphics::GraphicsAPIManager::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	BindElementBuffer();

	GraphicsAPI::UpdateDataToBuffer(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, indiceCount * sizeof(UINT32), indices);
	mNumOfIndices = indiceCount;
}
*/

const dooms::physics::AABB3D& dooms::graphics::Mesh::GetBoundingBox() const
{
	return mAABB3D;
}

const dooms::physics::Sphere& dooms::graphics::Mesh::GetBoundingSphere() const
{
	return mSphere;
}

const dooms::graphics::BufferID& dooms::graphics::Mesh::GetVertexArrayObjectID() const
{
	return mVertexArrayObjectID;
}

const dooms::graphics::BufferID& dooms::graphics::Mesh::GetElementBufferObjectID() const
{
	return mElementBufferObjectID;
}

void* dooms::graphics::Mesh::MapVertexDataBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexDataBuffer.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapVertexDataBuffer()
{
	if(mVertexDataBuffer.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER);
	}
}

void* dooms::graphics::Mesh::MapElementBuffer
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexArrayObjectID.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, mapBufferAccessOption);
	}
	D_ASSERT(bufferAddress != nullptr);

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapElementBuffer()
{
	if (mElementBufferObjectID.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER);
	}
}

UINT64 dooms::graphics::Mesh::GetNumOfIndices() const
{
	return mNumOfIndices;
}

UINT64 dooms::graphics::Mesh::GetNumOfVertices() const
{
	return mNumOfVertices;
}





