#include "Mesh.h"

#include <type_traits>
#include "../Graphics_Core.h"

void doom::graphics::Mesh::BufferData(GLsizeiptr size, const void* data) noexcept
{
	D_ASSERT(false);

	this->mNumOfVertices = 0;
	this->mNumOfIndices = 0;
	mPrimitiveType = ePrimitiveType::LINE;
}


void doom::graphics::Mesh::BufferDataFromModelMesh() noexcept
{
	this->BindBuffer(); // bind vertex array buffer

	auto& meshData = mThreeDModelMesh.get();

	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::remove_pointer_t<decltype(meshData.mMeshVertexDatas)>) * meshData.mNumOfVertexs, &(meshData.mMeshVertexDatas[0]), GL_STATIC_DRAW);

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

	this->mNumOfVertices = meshData.mNumOfVertexs;

	// only fill the index buffer if the index array is non-empty.
	this->mNumOfIndices = 0;
	if (meshData.bHasIndices == true && meshData.mNumOfIndices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mElementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.mNumOfIndices * sizeof(unsigned int), &(meshData.mMeshIndices[0]), GL_STATIC_DRAW);
		this->mNumOfIndices = meshData.mNumOfIndices;
	}

	mPrimitiveType = meshData.mPrimitiveType;
	
}

