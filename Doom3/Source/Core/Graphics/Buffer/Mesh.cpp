#include "Mesh.h"

#include "../GraphicsAPI.h"
#include "../Asset/ThreeDModelAsset.h"

dooms::graphics::Mesh::Mesh()
	: Buffer(), mVertexArrayObjectID{ INVALID_BUFFER_ID }, mElementBufferObjectID{ INVALID_BUFFER_ID }, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mPrimitiveType{ ePrimitiveType::NONE }
{

}

dooms::graphics::Mesh::Mesh(GLsizeiptr dataCount, const void* data, ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept
	: Buffer(), mTargetThreeDModelMesh{ nullptr }
{
	GenMeshBuffer(false);
	BufferData(dataCount, data, primitiveType, vertexArrayFlag);
}


dooms::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
	: Buffer(), mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mTargetThreeDModelMesh{&threeDModelMesh}
{
	GenMeshBuffer(threeDModelMesh.bHasIndices);
	BufferDataFromModelMesh(threeDModelMesh);
}

dooms::graphics::Mesh::~Mesh()
{
	DeleteBuffers();
	
}

void dooms::graphics::Mesh::GenMeshBuffer(bool hasIndice)
{
	Buffer::GenBuffer();
	if (mVertexArrayObjectID.GetBufferID() == INVALID_BUFFER_ID)
	{
		glGenVertexArrays(1, &(mVertexArrayObjectID));
	}
	if (hasIndice)
	{
		if (mElementBufferObjectID.GetBufferID() == INVALID_BUFFER_ID)
		{
			glGenBuffers(1, &(mElementBufferObjectID));
		}
	}
	else
	{
		mElementBufferObjectID = 0;
	}
}

void dooms::graphics::Mesh::DeleteBuffers()
{
	Buffer::DeleteBuffers();

	if (mVertexArrayObjectID.IsValid())
	{
		glDeleteVertexArrays(1, &(mVertexArrayObjectID));
		mVertexArrayObjectID = INVALID_BUFFER_ID;
	}
	if (mElementBufferObjectID.IsValid())
	{
		glDeleteBuffers(1, &(mElementBufferObjectID));
		mElementBufferObjectID = INVALID_BUFFER_ID;
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


void dooms::graphics::Mesh::BufferData(GLsizeiptr dataComponentCount, const void* data, ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept
{
	GenBufferIfNotGened(false);

	BindVertexArrayObject(); // bind vertex array buffer
	BindVertexBufferObject();

	D_DEBUG_LOG(eLogType::D_LOG, "%f", sizeof(FLOAT32) * dataComponentCount);
	glBufferData(GL_ARRAY_BUFFER, sizeof(FLOAT32) * dataComponentCount, data, GL_STATIC_DRAW);

	UINT32 offset = 0;
	const UINT32 stride = Mesh::GetStride(vertexArrayFlag);

#pragma warning( disable : 4312 )

	D_ASSERT(((vertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((vertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));


	if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		//mVertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 2 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 2 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

#pragma warning( disable : 4244 )
	mNumOfVertices = static_cast<UINT32>(dataComponentCount * sizeof(FLOAT32) / offset);
	mNumOfIndices = 0;
	
	mPrimitiveType = primitiveType;
	mVertexArrayFlag = vertexArrayFlag;
}

void dooms::graphics::Mesh::BufferSubData(GLsizeiptr dataComponentCount, const void* data, khronos_intptr_t offsetInByte) const noexcept
{
	D_ASSERT(mBufferID.IsValid());

	BindVertexArrayObject();
	BindVertexBufferObject();

	D_ASSERT(GraphicsAPI::GetInteger64v(GraphicsAPI::GetIntegerParameter::ARRAY_BUFFER_BINDING) == mBufferID);

	// GL_INVALID_VALUE is generated if offset or size is negative, or if offset+size is greater than the value of GL_BUFFER_SIZE for the specified buffer object.
	glBufferSubData(GL_ARRAY_BUFFER, offsetInByte, sizeof(FLOAT32) * dataComponentCount, data);

}

void dooms::graphics::Mesh::BindVertexBufferObject() const
{
	D_ASSERT(mBufferID.IsValid());

	if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_BUFFER_TAG, mBufferID))
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
	}

	
}


void dooms::graphics::Mesh::BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	GenBufferIfNotGened(threeDModelMesh.bHasIndices);

	BindVertexArrayObject(); // bind vertex array buffer first
	BindVertexBufferObject();

	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertexData) * threeDModelMesh.mMeshVertexDatas.size(), threeDModelMesh.mMeshVertexDatas.data(), GL_STATIC_DRAW);
	
	size_t offset = 0;
	const UINT32 stride = sizeof(MeshVertexData);

	//mVertex
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	//mTexCoord
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 2 * sizeof(FLOAT32);
	}

	//mNormal
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	//mTangent
	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	if (threeDModelMesh.mVertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(FLOAT32);
	}

	mNumOfVertices = threeDModelMesh.mMeshVertexDatas.size();

	// only fill the index buffer if the index array is non-empty.
	mNumOfIndices = 0;
	if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mMeshIndices.size() > 0)
	{
		BindElementBuffer();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, threeDModelMesh.mMeshIndices.size() * sizeof(UINT32), &(threeDModelMesh.mMeshIndices[0]), GL_STATIC_DRAW);
		mNumOfIndices = threeDModelMesh.mMeshIndices.size();
	}

	mPrimitiveType = threeDModelMesh.mPrimitiveType;

	mAABB3D = threeDModelMesh.mAABB3D;
	mSphere = threeDModelMesh.mSphere;

	mVertexArrayFlag = threeDModelMesh.mVertexArrayFlag;

	D_ASSERT(mPrimitiveType != ePrimitiveType::NONE);
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
	return Buffer::IsBufferGenerated() && mVertexArrayObjectID != 0;
}

void dooms::graphics::Mesh::UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount)
{
	D_ASSERT(IsBufferGenerated() == true);

	BindVertexArrayObject();
	BindElementBuffer();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceCount * sizeof(UINT32), indices, GL_STATIC_DRAW);
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

UINT32 dooms::graphics::Mesh::GetVertexArrayObjectID() const
{
	return mVertexArrayObjectID;
}

UINT32 dooms::graphics::Mesh::GetElementBufferObjectID() const
{
	return mElementBufferObjectID;
}





