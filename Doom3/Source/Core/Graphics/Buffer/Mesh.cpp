#include "Mesh.h"

#include <type_traits>
#include "../Graphics_Core.h"

doom::graphics::Mesh::Mesh()
	: Buffer(false), mVertexArrayObject{ 0 }, mElementBufferObject{ 0 }, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }, mPrimitiveType{ ePrimitiveType::NONE }
{

}

doom::graphics::Mesh::Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
	: Buffer(true), mNumOfVertices{ 0 }, mNumOfIndices{ 0 }
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
	Buffer::GenBuffer();

	this->GenMeshBuffer(threeDModelMesh.bHasIndices);

	this->BufferDataFromModelMesh(threeDModelMesh);
	return *this;
}


void doom::graphics::Mesh::BufferData(GLsizeiptr size, const void* data) noexcept
{
	D_ASSERT(false);

	this->mNumOfVertices = 0;
	this->mNumOfIndices = 0;
	mPrimitiveType = ePrimitiveType::NONE;
}


void doom::graphics::Mesh::BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept
{
	this->BindBuffer(); // bind vertex array buffer


	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::remove_pointer_t<decltype(threeDModelMesh.mMeshVertexDatas)>) * threeDModelMesh.mNumOfVertexs, &(threeDModelMesh.mMeshVertexDatas[0]), GL_STATIC_DRAW);

	size_t offset = 0;

	//mVertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	offset += 3;

	//mTexCoord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	offset += 2;

	//mNormal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	offset += 3;

	//mTangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
	offset += 3;

	//mBitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);

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

