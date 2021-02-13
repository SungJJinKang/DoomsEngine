#include "Mesh.h"

#include <utility>
#include <type_traits>
#include "../Graphics_Core.h"
#include "../Asset/ThreeDModelAsset.h"

doom::graphics::Mesh::Mesh()
	: Buffer(), mVertexArrayObject{ 0 }, mElementBufferObject{ 0 }, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mPrimitiveType{ ePrimitiveType::NONE }
{

}

doom::graphics::Mesh::Mesh(GLsizeiptr dataCount, const void* data, unsigned int vertexArrayFlag) noexcept : Buffer()
{
	this->GenMeshBuffer(false);
	this->BufferData(dataCount, data, vertexArrayFlag);
}

doom::graphics::Mesh::Mesh(Mesh&& mesh) noexcept : Buffer(std::move(mesh)), mVertexArrayObject{ mesh.mVertexArrayObject }, mVertexBufferObject{ mesh.mVertexBufferObject }
, mElementBufferObject{ mesh.mElementBufferObject }, mNumOfIndices{ mesh.mNumOfIndices }, mNumOfVertices{ mesh.mNumOfVertices }
, mPrimitiveType{ mesh.mPrimitiveType }
{
	mesh.mVertexArrayObject = 0;
	mesh.mVertexBufferObject = 0;
	mesh.mElementBufferObject = 0;
	mesh.mNumOfIndices = 0;
	mesh.mNumOfVertices = 0;
	mesh.mPrimitiveType = ePrimitiveType::NONE;

}


doom::graphics::Mesh& doom::graphics::Mesh::operator=(Mesh&& mesh) noexcept
{
	this->mVertexArrayObject = mesh.mVertexArrayObject;
	this->mVertexBufferObject = mesh.mVertexBufferObject;
	this->mElementBufferObject = mesh.mElementBufferObject;
	this->mNumOfIndices = mesh.mNumOfIndices;
	this->mNumOfVertices = mesh.mNumOfVertices;
	this->mPrimitiveType = mesh.mPrimitiveType;

	mesh.mVertexArrayObject = 0;
	mesh.mVertexBufferObject = 0;
	mesh.mElementBufferObject = 0;
	mesh.mNumOfIndices = 0;
	mesh.mNumOfVertices = 0;
	mesh.mPrimitiveType = ePrimitiveType::NONE;
	return *this;
}


doom::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
	: Buffer(), mNumOfVertices{ 0 }, mNumOfIndices{ 0 }
{
	this->GenMeshBuffer(threeDModelMesh.bHasIndices);
	this->BufferDataFromModelMesh(threeDModelMesh);
}

doom::graphics::Mesh::~Mesh()
{
	this->DeleteBuffers();
}

void doom::graphics::Mesh::GenMeshBuffer(bool hasIndice)
{
	Buffer::GenBuffer();
	glGenVertexArrays(1, &(this->mVertexArrayObject));
	if (hasIndice)
	{
		glGenBuffers(1, &(this->mElementBufferObject));
	}
	else
	{
		this->mElementBufferObject = 0;
	}
}

void doom::graphics::Mesh::DeleteBuffers()
{
	Buffer::DeleteBuffers();

	if (this->mVertexArrayObject != 0)
	{
		glDeleteVertexArrays(1, &(this->mVertexArrayObject));
	}
	if (this->mElementBufferObject != 0)
	{
		glDeleteBuffers(1, &(this->mElementBufferObject));
	}
}

doom::graphics::Mesh& doom::graphics::Mesh::operator=(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	this->DeleteBuffers();

	this->GenMeshBuffer(threeDModelMesh.bHasIndices);

	this->BufferDataFromModelMesh(threeDModelMesh);
	return *this;
}


void doom::graphics::Mesh::BufferData(GLsizeiptr dataCount, const void* data, unsigned int vertexArrayFlag) noexcept
{
	this->BindBuffer(); // bind vertex array buffer


	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataCount, data, GL_STATIC_DRAW);

	unsigned int offset = 0;
	unsigned int stride = Mesh::GetStride(vertexArrayFlag);

#pragma warning( disable : 4312 )

	if (vertexArrayFlag & eVertexArrayFlag::Vertex)
	{
		//mVertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3;
	}
	
	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 2;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3;
	}

#pragma warning( disable : 4244 )
	this->mNumOfVertices = dataCount / offset;
	this->mNumOfIndices = 0;

	mPrimitiveType = ePrimitiveType::TRIANGLE;
}


void doom::graphics::Mesh::BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	this->BindBuffer(); // bind vertex array buffer first

	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject); // and bind VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::remove_pointer_t<decltype(threeDModelMesh.mMeshVertexDatas)>) * threeDModelMesh.mNumOfVertexs, &(threeDModelMesh.mMeshVertexDatas[0]), GL_STATIC_DRAW);

	size_t offset = 0;
	unsigned int stride = 14 * sizeof(float);

	//mVertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3;

	//mTexCoord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 2;

	//mNormal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3;

	//mTangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3;

	//mBitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
	offset += 3;

	this->mNumOfVertices = threeDModelMesh.mNumOfVertexs;

	// only fill the index buffer if the index array is non-empty.
	this->mNumOfIndices = 0;
	if (threeDModelMesh.bHasIndices == true && threeDModelMesh.mNumOfIndices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mElementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, threeDModelMesh.mNumOfIndices * sizeof(unsigned int), &(threeDModelMesh.mMeshIndices[0]), GL_STATIC_DRAW);
		this->mNumOfIndices = threeDModelMesh.mNumOfIndices;
	}

	this->mPrimitiveType = threeDModelMesh.mPrimitiveType;
	D_ASSERT(this->mPrimitiveType != ePrimitiveType::NONE);
}

constexpr unsigned int doom::graphics::Mesh::GetStride(unsigned int vertexArrayFlag)
{
	unsigned int offset = 0;
	if (vertexArrayFlag & eVertexArrayFlag::Vertex)
	{
		//mVertex
		offset += 3;
	}

	if (vertexArrayFlag & eVertexArrayFlag::TexCoord)
	{
		//mTexCoord
		offset += 2;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mNormal)
	{
		//mNormal
		offset += 3;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mTangent)
	{
		//mTangent
		offset += 3;
	}

	if (vertexArrayFlag & eVertexArrayFlag::mBitangent)
	{
		//mBitangent
		offset += 3;
	}

	return offset * sizeof(float);
}

static constexpr float QuadMeshData[]
{
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

const doom::graphics::Mesh& doom::graphics::Mesh::GetQuadMesh()
{
	if (doom::graphics::Mesh::QuadMesh == nullptr)
	{
		doom::graphics::Mesh::QuadMesh = new doom::graphics::Mesh(sizeof(QuadMeshData) / sizeof(float), (void*)QuadMeshData, eVertexArrayFlag::Vertex | eVertexArrayFlag::TexCoord);
	}

	return *doom::graphics::Mesh::QuadMesh;
}



