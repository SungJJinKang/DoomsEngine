#include "Mesh.h"


#include "../Asset/ThreeDModelAsset.h"

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
	const long long int dataCount, 
	const void* data, 
	GraphicsAPI::ePrimitiveType primitiveType,
	UINT32 vertexArrayFlag
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
	CreateBufferObject(dataCount, data, primitiveType, vertexArrayFlag);
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

void dooms::graphics::Mesh::BindVertexArrayObject() const
{
	if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		D_ASSERT(mVertexArrayObjectID.IsValid() == true);
		dooms::graphics::GraphicsAPI::BindVertexArrayObject(mVertexArrayObjectID);
	}
}

void dooms::graphics::Mesh::BindVertexBufferObject() const
{
	D_ASSERT(mVertexDataBuffer.IsValid() == true);
	D_ASSERT(mTotalStride > 0);

	if(graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		dooms::graphics::GraphicsAPI::BindVertexDataBuffer
		(
			mVertexDataBuffer,
			0,
			mTotalStride,
			0
		);
	}
	else if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		for(size_t bufferLayoutIndex = 0 ; bufferLayoutIndex < mVertexBufferLayoutCount ; bufferLayoutIndex++)
		{
			dooms::graphics::GraphicsAPI::BindVertexDataBuffer
			(
				mVertexDataBuffer,
				bufferLayoutIndex,
				mVertexBufferLayouts[bufferLayoutIndex].mStride,
				mVertexBufferLayouts[bufferLayoutIndex].mOffset
			);
		}
		
	}
	else
	{
		NEVER_HAPPEN;
	}
	
}

void dooms::graphics::Mesh::BindIndexBufferObject() const
{
	D_ASSERT(mVertexDataBuffer.IsValid() == true);
	dooms::graphics::GraphicsAPI::BindBuffer(mElementBufferObjectID, 0, graphics::GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, graphics::GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

}

void dooms::graphics::Mesh::BindVertexBufferObject
(
	const UINT32 bindingPosition, 
	const UINT32 stride,
	const UINT32 offset
) const
{
	D_ASSERT(mVertexDataBuffer.IsValid() == true);
	dooms::graphics::GraphicsAPI::BindVertexDataBuffer
	(
		mVertexDataBuffer,
		bindingPosition,
		stride,
		offset
	);
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
	const long long int dataComponentCount, 
	const void* data, 
	GraphicsAPI::ePrimitiveType primitiveType,
	UINT32 vertexArrayFlag
) noexcept
{
	D_ASSERT(IsBufferGenerated() == false);
	if (IsBufferGenerated() == false)
	{
		if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			CreateVertexArrayObjectIfNotExist();
		}

		const UINT32 stride = Mesh::GetStride(vertexArrayFlag);
		mTotalStride = stride;

		BindVertexArrayObject(); // bind vertex array buffer

		D_DEBUG_LOG(eLogType::D_LOG, "%f", sizeof(FLOAT32) * dataComponentCount);
		mVertexDataBuffer = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ARRAY_BUFFER, static_cast<unsigned long long>(sizeof(FLOAT32) * dataComponentCount), data);
		BindVertexBufferObject();

		UINT32 offset = 0;
		
#pragma warning( disable : 4312 )

		D_ASSERT(((vertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((vertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));


		UINT32 vertexLayoutCount = 0;
		if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mVertex
				GraphicsAPI::EnableVertexAttributeArrayIndex(0);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 0, 2, sizeof(math::Vector2), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector2);
			vertexLayoutCount++;

			offset += 2 * sizeof(FLOAT32);
		}

		if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mVertex
				GraphicsAPI::EnableVertexAttributeArrayIndex(0);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 0, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;

			offset += 3 * sizeof(FLOAT32);
		}

		if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mTexCoord
				GraphicsAPI::EnableVertexAttributeArrayIndex(1);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 1, 2, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;

			offset += 2 * sizeof(FLOAT32);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mNormal)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mNormal
				GraphicsAPI::EnableVertexAttributeArrayIndex(2);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 2, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;

			offset += 3 * sizeof(FLOAT32);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mTangent)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mTangent
				GraphicsAPI::EnableVertexAttributeArrayIndex(3);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 3, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;

			offset += 3 * sizeof(FLOAT32);
		}

		if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
		{
			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				//mBitangent
				GraphicsAPI::EnableVertexAttributeArrayIndex(4);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 4, 3, sizeof(math::Vector3), offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = sizeof(math::Vector3);
			vertexLayoutCount++;

			offset += 3 * sizeof(FLOAT32);
		}

		mVertexBufferLayoutCount = vertexLayoutCount;
	

#pragma warning( disable : 4244 )
		mNumOfVertices = static_cast<UINT32>(dataComponentCount * sizeof(FLOAT32) / offset);
		mNumOfIndices = 0;

		mPrimitiveType = primitiveType;
		mVertexArrayFlag = vertexArrayFlag;

	}
}

void dooms::graphics::Mesh::UpdateVertexData
(
	const long long int dataComponentCount, 
	const void* data, 
	const long long int offsetInByte
) const noexcept
{
	D_ASSERT(mVertexDataBuffer.IsValid());
	
	BindVertexBufferObject();
	GraphicsAPI::UpdateDataToBuffer(mVertexDataBuffer, GraphicsAPI::ARRAY_BUFFER, offsetInByte, sizeof(FLOAT32) * dataComponentCount, data);
}


void dooms::graphics::Mesh::CreateVertexArrayObjectIfNotExist()
{
	D_ASSERT(graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL);
	
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
		if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
		{
			CreateVertexArrayObjectIfNotExist();
		}

		mTotalStride = GetStride(mVertexArrayFlag);

		BindVertexArrayObject(); // bind vertex array buffer

		mVertexDataBuffer = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ARRAY_BUFFER, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), threeDModelMesh.mMeshDatas.mData);
		D_ASSERT(mVertexDataBuffer.IsValid());
		//GraphicsAPI::UpdateDataToBuffer(mVertexDataBuffer, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, 0, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), reinterpret_cast<const void*>(threeDModelMesh.mMeshDatas.mData));

		UINT32 vertexLayoutCount = 0;

		//mVertex
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::VertexVector3)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mVertex));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mVertex - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(0);
				GraphicsAPI::EnableVertexAttributeArrayIndex(0); GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 0, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
		}

		//mTexCoord
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::TexCoord)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mTexCoord));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTexCoord - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(1);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 1, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
		}

		//mNormal
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mNormal)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mNormal));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mNormal - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(2);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 2, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
		}

		//mTangent
		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mTangent)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mTangent));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTangent - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(3);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 3, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
		}

		if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mBitangent)
		{
			const UINT32 stride = sizeof(*(threeDModelMesh.mMeshDatas.mBitangent));
			const UINT64 offset = static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mBitangent - threeDModelMesh.mMeshDatas.mData);

			if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
			{
				GraphicsAPI::EnableVertexAttributeArrayIndex(4);
				GraphicsAPI::DefineVertexAttributeLayout(mVertexDataBuffer, 4, 3, stride, offset);
			}

			mVertexBufferLayouts[vertexLayoutCount].mOffset = offset;
			mVertexBufferLayouts[vertexLayoutCount].mStride = stride;
			vertexLayoutCount++;
		}

		mVertexBufferLayoutCount = vertexLayoutCount;
		mNumOfVertices = threeDModelMesh.mMeshDatas.mVerticeCount;

		// only fill the index buffer if the index array is non-empty.
		mNumOfIndices = 0;
		if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mMeshIndices.size() > 0)
		{
			mElementBufferObjectID = GraphicsAPI::CreateBufferObject(GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), NULL);
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
	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		offset += 2 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		offset += 3 * sizeof(FLOAT32);
	}

	return offset;
}



bool dooms::graphics::Mesh::IsBufferGenerated() const
{
	if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		return mVertexDataBuffer.IsValid() && mVertexArrayObjectID.IsValid();
	}
	else if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::DX11_10)
	{
		return mVertexDataBuffer.IsValid();
	}
	else
	{
		NEVER_HAPPEN;
		return false;
	}
}

void dooms::graphics::Mesh::UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount)
{
	D_ASSERT(IsBufferGenerated() == true);

	if (graphics::GraphicsAPI::GetCurrentAPIType() == graphics::GraphicsAPI::eGraphicsAPIType::OpenGL)
	{
		BindVertexArrayObject();
	}
	BindElementBuffer();

	GraphicsAPI::UpdateDataToBuffer(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, indiceCount * sizeof(UINT32), indices);
	mNumOfIndices = indiceCount;
}

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

void* dooms::graphics::Mesh::GetMappedVertexArrayObject
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexArrayObjectID.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mVertexArrayObjectID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, mapBufferAccessOption);
	}

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapMappedVertexArrayObject()
{
	if(mVertexArrayObjectID.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mVertexArrayObjectID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER);
	}
}

void* dooms::graphics::Mesh::GetMappedElementBufferObjectObject
(
	const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
)
{
	void* bufferAddress = nullptr;
	if (mVertexArrayObjectID.IsValid() == true)
	{
		bufferAddress = GraphicsAPI::MapBufferObjectToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, mapBufferAccessOption);
	}

	return bufferAddress;
}

void dooms::graphics::Mesh::UnmapMappedElementBufferObjectObject()
{
	if (mElementBufferObjectID.IsValid() == true)
	{
		GraphicsAPI::UnMapBufferObjectMappedToClientAddress(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER);
	}
}





