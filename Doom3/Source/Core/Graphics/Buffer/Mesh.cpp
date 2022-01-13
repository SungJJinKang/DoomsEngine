#include "Mesh.h"


#include "../Asset/ThreeDModelAsset.h"

dooms::graphics::Mesh::Mesh()
	: Buffer(), mVertexArrayObjectID{ }, mElementBufferObjectID{ }, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mPrimitiveType{ GraphicsAPI::ePrimitiveType::NONE }
{

}

dooms::graphics::Mesh::Mesh(const long long int dataCount, const void* data, GraphicsAPI::ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept
	: Buffer(), mTargetThreeDModelMesh{ nullptr }, mVertexArrayObjectID{ }, mElementBufferObjectID{ }
{
	GenMeshBuffer(false);
	BufferData(dataCount, data, primitiveType, vertexArrayFlag);
}


dooms::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
	: Buffer(), mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mTargetThreeDModelMesh{&threeDModelMesh}, mVertexArrayObjectID{ }, mElementBufferObjectID{ }
{
	GenMeshBuffer(threeDModelMesh.bHasIndices);
	BufferDataFromModelMesh(threeDModelMesh);
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

void dooms::graphics::Mesh::GenMeshBuffer(bool hasIndice)
{
	Buffer::GenBuffer();
	if (mVertexArrayObjectID.IsValid() == false)
	{
		mVertexArrayObjectID = GraphicsAPI::CreateVertexArrayObject();
	}
	if (hasIndice)
	{
		if (mElementBufferObjectID.IsValid() == false)
		{
			mElementBufferObjectID = GraphicsAPI::CreateBuffer();;
		}
	}
	else
	{
		mElementBufferObjectID.Reset();
	}
}

void dooms::graphics::Mesh::DeleteBuffers()
{
	Buffer::DeleteBuffers();

	if (mVertexArrayObjectID.IsValid())
	{
		GraphicsAPI::DestroyVertexArrayObject(mVertexArrayObjectID);
		mVertexArrayObjectID.Reset();
	}
	if (mElementBufferObjectID.IsValid())
	{
		GraphicsAPI::DestroyBuffer( mElementBufferObjectID );
		mElementBufferObjectID.Reset();
	}
}

void dooms::graphics::Mesh::GenBufferIfNotGened(bool hasIndice)
{
	if (IsBufferGenerated() == false)
	{
		GenMeshBuffer(hasIndice);
	}
}

dooms::graphics::Mesh& dooms::graphics::Mesh::operator=(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	DeleteBuffers();

	mTargetThreeDModelMesh = &threeDModelMesh;
	GenMeshBuffer(threeDModelMesh.bHasIndices);

	BufferDataFromModelMesh(threeDModelMesh);
	return *this;
}


const dooms::ThreeDModelMesh* dooms::graphics::Mesh::GetTargetThreeDModelMesh() const
{
	return mTargetThreeDModelMesh;
}

void dooms::graphics::Mesh::BufferData
(
	const long long int dataComponentCount, 
	const void* data, 
	GraphicsAPI::ePrimitiveType primitiveType,
	UINT32 vertexArrayFlag
) noexcept
{
	GenBufferIfNotGened(false);

	BindVertexArrayObject(); // bind vertex array buffer

	D_DEBUG_LOG(eLogType::D_LOG, "%f", sizeof(FLOAT32) * dataComponentCount);
	GraphicsAPI::AllocateBufferMemory(mBufferID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, sizeof(FLOAT32) * dataComponentCount, data);

	UINT32 offset = 0;
	const UINT32 stride = Mesh::GetStride(vertexArrayFlag);

#pragma warning( disable : 4312 )

	D_ASSERT(((vertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((vertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));


	if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		//mVertex
		GraphicsAPI::EnableVertexAttributeArrayIndex(0);
		GraphicsAPI::DefineVertexAttributeLayout(0, 2, stride, offset);
		offset += 2 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		GraphicsAPI::EnableVertexAttributeArrayIndex(0);
		GraphicsAPI::DefineVertexAttributeLayout(0, 3, stride, offset);
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		GraphicsAPI::EnableVertexAttributeArrayIndex(1);
		GraphicsAPI::DefineVertexAttributeLayout(1, 2, stride, offset);
		offset += 2 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		GraphicsAPI::EnableVertexAttributeArrayIndex(2);
		GraphicsAPI::DefineVertexAttributeLayout(2, 3, stride, offset);
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		GraphicsAPI::EnableVertexAttributeArrayIndex(3);
		GraphicsAPI::DefineVertexAttributeLayout(3, 3, stride, offset);
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		GraphicsAPI::EnableVertexAttributeArrayIndex(4);
		GraphicsAPI::DefineVertexAttributeLayout(4, 3, stride, offset);
		offset += 3 * sizeof(FLOAT32);
	}

#pragma warning( disable : 4244 )
	mNumOfVertices = static_cast<UINT32>(dataComponentCount * sizeof(FLOAT32) / offset);
	mNumOfIndices = 0;
	
	mPrimitiveType = primitiveType;
	mVertexArrayFlag = vertexArrayFlag;
}

void dooms::graphics::Mesh::BufferSubData
(
	const long long int dataComponentCount, 
	const void* data, 
	const long long int offsetInByte
) const noexcept
{
	D_ASSERT(mBufferID.IsValid());

	BindVertexArrayObject();
	BindVertexBufferObject();

	//D_ASSERT(GraphicsAPI::GetInteger64v(GraphicsAPI::GetIntegerParameter::ARRAY_BUFFER_BINDING) == mBufferID);

	// GL_INVALID_VALUE is generated if offset or size is negative, or if offset+size is greater than the value of GL_BUFFER_SIZE for the specified buffer object.
	GraphicsAPI::UpdateDataToBuffer(mBufferID, GraphicsAPI::ARRAY_BUFFER, offsetInByte, sizeof(FLOAT32) * dataComponentCount, data);

}

void dooms::graphics::Mesh::BindVertexBufferObject() const
{
	D_ASSERT(mBufferID.IsValid());

	if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_BUFFER_TAG, mBufferID))
	{
		GraphicsAPI::BindBuffer(mBufferID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER);
	}

	
}


void dooms::graphics::Mesh::BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	GenBufferIfNotGened(threeDModelMesh.bHasIndices);

	BindVertexArrayObject(); // bind vertex array buffer first
	
	GraphicsAPI::AllocateBufferMemory(mBufferID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), NULL);
	GraphicsAPI::UpdateDataToBuffer(mBufferID, GraphicsAPI::eBufferTarget::ARRAY_BUFFER, 0, threeDModelMesh.mMeshDatas.GetAllocatedDataSize(), threeDModelMesh.mMeshDatas.mData);
	
	//mVertex
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		GraphicsAPI::EnableVertexAttributeArrayIndex(0);
		GraphicsAPI::DefineVertexAttributeLayout(0, 3, sizeof(*(threeDModelMesh.mMeshDatas.mVertex)), static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mVertex - threeDModelMesh.mMeshDatas.mData));
	}

	//mTexCoord
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		GraphicsAPI::EnableVertexAttributeArrayIndex(1);
		GraphicsAPI::DefineVertexAttributeLayout(1, 3, sizeof(*(threeDModelMesh.mMeshDatas.mTexCoord)), static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTexCoord - threeDModelMesh.mMeshDatas.mData));
	}

	//mNormal
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		GraphicsAPI::EnableVertexAttributeArrayIndex(2);
		GraphicsAPI::DefineVertexAttributeLayout(2, 3, sizeof(*(threeDModelMesh.mMeshDatas.mNormal)), static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mNormal - threeDModelMesh.mMeshDatas.mData));
	}

	//mTangent
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		GraphicsAPI::EnableVertexAttributeArrayIndex(3);
		GraphicsAPI::DefineVertexAttributeLayout(3, 3, sizeof(*(threeDModelMesh.mMeshDatas.mTangent)), static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mTangent - threeDModelMesh.mMeshDatas.mData));
	}

	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		GraphicsAPI::EnableVertexAttributeArrayIndex(4);
		GraphicsAPI::DefineVertexAttributeLayout(4, 3, sizeof(*(threeDModelMesh.mMeshDatas.mBitangent)), static_cast<unsigned int>((char*)threeDModelMesh.mMeshDatas.mBitangent - threeDModelMesh.mMeshDatas.mData));
	}

	mNumOfVertices = threeDModelMesh.mMeshDatas.mVerticeCount;

	// only fill the index buffer if the index array is non-empty.
	mNumOfIndices = 0;
	if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mMeshIndices.size() > 0)
	{
		GraphicsAPI::AllocateBufferMemory(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), NULL);
		GraphicsAPI::UpdateDataToBuffer(mElementBufferObjectID, GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER, 0, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), reinterpret_cast<const void*>(threeDModelMesh.mMeshIndices.data()));
		mNumOfIndices = threeDModelMesh.mMeshIndices.size();
	}

	mPrimitiveType = threeDModelMesh.mPrimitiveType;

	mAABB3D = threeDModelMesh.mAABB3D;
	mSphere = threeDModelMesh.mSphere;

	mVertexArrayFlag = threeDModelMesh.mVertexArrayFlag;

	D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);
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
	return Buffer::IsBufferGenerated() && mVertexArrayObjectID.IsValid();
}

void dooms::graphics::Mesh::UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount)
{
	D_ASSERT(IsBufferGenerated() == true);

	BindVertexArrayObject();
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





