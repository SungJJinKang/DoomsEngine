#include "Mesh.h"

#include <utility>
#include <type_traits>
#include "../Graphics_Core.h"
#include "../GraphicsAPI.h"
#include "../Asset/ThreeDModelAsset.h"

doom::graphics::Mesh::Mesh()
	: Buffer(), mVertexArrayObjectID{ 0 }, mElementBufferObjectID{ 0 }, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mPrimitiveType{ ePrimitiveType::NONE }
{

}

doom::graphics::Mesh::Mesh(GLsizeiptr dataCount, const void* data, ePrimitiveType primitiveType, unsigned int vertexArrayFlag) noexcept : Buffer()
{
	GenMeshBuffer(false);
	BufferData(dataCount, data, primitiveType, vertexArrayFlag);
}


doom::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
	: Buffer(), mNumOfVertices{ 0 }, mNumOfIndices{ 0 }
{
	GenMeshBuffer(threeDModelMesh.bHasIndices);
	BufferDataFromModelMesh(threeDModelMesh);
}

doom::graphics::Mesh::~Mesh()
{
	DeleteBuffers();
}

void doom::graphics::Mesh::GenMeshBuffer(bool hasIndice)
{
	Buffer::GenBuffer();
	if (mVertexArrayObjectID.Get() == 0)
	{
		glGenVertexArrays(1, &(mVertexArrayObjectID));
	}
	if (hasIndice)
	{
		if (mElementBufferObjectID.Get() == 0)
		{
			glGenBuffers(1, &(mElementBufferObjectID));
		}
	}
	else
	{
		mElementBufferObjectID = 0;
	}
}

void doom::graphics::Mesh::DeleteBuffers()
{
	Buffer::DeleteBuffers();

	if (mVertexArrayObjectID != 0)
	{
		glDeleteVertexArrays(1, &(mVertexArrayObjectID));
		mVertexArrayObjectID = 0;
	}
	if (mElementBufferObjectID != 0)
	{
		glDeleteBuffers(1, &(mElementBufferObjectID));
		mElementBufferObjectID = 0;
	}
}

void doom::graphics::Mesh::GenBufferIfNotGened(bool hasIndice)
{
	if (IsBufferGenerated() == true)
		return;

	GenMeshBuffer(hasIndice);
}

doom::graphics::Mesh& doom::graphics::Mesh::operator=(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	DeleteBuffers();

	GenMeshBuffer(threeDModelMesh.bHasIndices);

	BufferDataFromModelMesh(threeDModelMesh);
	return *this;
}


void doom::graphics::Mesh::BufferData(GLsizeiptr dataComponentCount, const void* data, ePrimitiveType primitiveType, unsigned int vertexArrayFlag) noexcept
{
	GenBufferIfNotGened(false);

	BindVertexArrayObject(); // bind vertex array buffer
	BindVertexBufferObject();

	D_DEBUG_LOG(std::to_string(sizeof(float) * dataComponentCount));
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataComponentCount, data, GL_STATIC_DRAW);

	unsigned int offset = 0;
	const unsigned int stride = Mesh::GetStride(vertexArrayFlag);

#pragma warning( disable : 4312 )

	D_ASSERT(((vertexArrayFlag & eVertexArrayFlag::VertexVector2)) > 0 != ((vertexArrayFlag & eVertexArrayFlag::VertexVector3) > 0));


	if (vertexArrayFlag & eVertexArrayFlag::VertexVector2)
	{
		//mVertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 2 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 2 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		offset += 3 * sizeof(float);
	}

#pragma warning( disable : 4244 )
	mNumOfVertices = static_cast<unsigned int>(dataComponentCount * sizeof(float) / offset);
	mNumOfIndices = 0;
	
	mPrimitiveType = primitiveType;

	mVertexArrayFlag = mVertexArrayFlag;
}

void doom::graphics::Mesh::BufferSubData(GLsizeiptr dataComponentCount, const void* data, khronos_intptr_t offsetInByte) noexcept
{
	D_ASSERT(mBufferID != 0);

	BindVertexArrayObject();
	BindVertexBufferObject();

	D_ASSERT(GraphicsAPI::GetInteger64v(GraphicsAPI::GetIntegerParameter::ARRAY_BUFFER_BINDING) == mBufferID);

	// GL_INVALID_VALUE is generated if offset or size is negative, or if offset+size is greater than the value of GL_BUFFER_SIZE for the specified buffer object.
	glBufferSubData(GL_ARRAY_BUFFER, offsetInByte, sizeof(float) * dataComponentCount, data);

}

void doom::graphics::Mesh::BindVertexBufferObject()
{
	D_ASSERT(mBufferID != 0);

	if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_BUFFER_TAG, mBufferID))
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
	}

	
}


void doom::graphics::Mesh::BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	GenBufferIfNotGened(threeDModelMesh.bHasIndices);

	BindVertexArrayObject(); // bind vertex array buffer first
	BindVertexBufferObject();

	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertexData) * threeDModelMesh.mNumOfVertexs, threeDModelMesh.mMeshVertexDatas.get(), GL_STATIC_DRAW);
	
	size_t offset = 0;
	const unsigned int stride = 14 * sizeof(float);

	//mVertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
	offset += 3 * sizeof(float);

	//mTexCoord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
	offset += 2 * sizeof(float);

	//mNormal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
	offset += 3 * sizeof(float);

	//mTangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
	offset += 3 * sizeof(float);

	//mBitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
	offset += 3 * sizeof(float);

	mNumOfVertices = threeDModelMesh.mNumOfVertexs;

	// only fill the index buffer if the index array is non-empty.
	mNumOfIndices = 0;
	if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mNumOfIndices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, threeDModelMesh.mNumOfIndices * sizeof(unsigned int), &(threeDModelMesh.mMeshIndices[0]), GL_STATIC_DRAW);
		mNumOfIndices = threeDModelMesh.mNumOfIndices;
	}

	mPrimitiveType = threeDModelMesh.mPrimitiveType;

	mAABB3D = threeDModelMesh.mAABB3D;
	mSphere = threeDModelMesh.mSphere;

	D_ASSERT(mPrimitiveType != ePrimitiveType::NONE);
}

constexpr unsigned int doom::graphics::Mesh::GetStride(unsigned int vertexArrayFlag)
{
	unsigned int offset = 0;
	if (vertexArrayFlag & eVertexArrayFlag::VertexVector3)
	{
		//mVertex
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		offset += 2 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		offset += 3 * sizeof(float);
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		offset += 3 * sizeof(float);
	}

	return offset;
}

inline static constexpr float QuadMeshData[]
{
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

std::shared_ptr<doom::graphics::Mesh> doom::graphics::Mesh::GetQuadMesh()
{
	if (doom::graphics::Mesh::QuadMesh == nullptr)
	{
		doom::graphics::Mesh::QuadMesh = std::make_shared<Mesh>(sizeof(QuadMeshData) / sizeof(float), (void*)QuadMeshData, ePrimitiveType::TRIANGLES, eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord);
	}

	return doom::graphics::Mesh::QuadMesh;
}

doom::graphics::Mesh doom::graphics::Mesh::GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup)
{
	float QuadMeshData[]
	{
		leftbottom.x, rightup.y, 0.0f, 0.0f, 1.0f,
		leftbottom.x, leftbottom.y, 0.0f, 0.0f, 0.0f,
		rightup.x, leftbottom.y, 0.0f, 1.0f, 0.0f,

		rightup.x, leftbottom.y, 0.0f, 1.0f, 0.0f,
		rightup.x, rightup.y, 0.0f, 1.0f, 1.0f,
		leftbottom.x, rightup.y, 0.0f, 0.0f, 1.0f,
	};

	return Mesh(sizeof(QuadMeshData) / sizeof(float), (void*)QuadMeshData, ePrimitiveType::TRIANGLES, eVertexArrayFlag::VertexVector3 | eVertexArrayFlag::TexCoord);
}


bool doom::graphics::Mesh::IsBufferGenerated()
{
	return Buffer::IsBufferGenerated() && mVertexArrayObjectID != 0;
}

const doom::physics::AABB3D& doom::graphics::Mesh::GetAABB() const
{
	return mAABB3D;
}

unsigned int doom::graphics::Mesh::GetVertexArrayObjectID()
{
	return mVertexArrayObjectID;
}

unsigned int doom::graphics::Mesh::GetElementBufferObjectID()
{
	return mElementBufferObjectID;
}

doom::physics::AABB3D doom::graphics::Mesh::GetAABB()
{
	return mAABB3D;
}

const doom::physics::Sphere& doom::graphics::Mesh::GetSphere() const
{
	return mSphere;
}

doom::physics::Sphere doom::graphics::Mesh::GetSphere()
{
	return mSphere;
}



