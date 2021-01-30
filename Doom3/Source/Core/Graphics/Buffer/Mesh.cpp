#include "Mesh.h"

#include <type_traits>
#include "../Graphics_Core.h"

void doom::graphics::Mesh::BufferData(GLsizeiptr size, const void* data) noexcept
{
	// configure vertex attributes (only on vertex data size() > 0)
	this->BindBuffer();

	auto& meshData = mThreeDModelMesh.get();
	// only fill the index buffer if the index array is non-empty.
	if (meshData.bHasIndices == true && meshData.mNumOfIndices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mElementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.mNumOfIndices * sizeof(unsigned int), &(meshData.mMeshIndices[0]), GL_STATIC_DRAW);
	}


	/*
		Vector3 mVertex;
		Vector2 mTexCoord; //support only one channel
		Vector3 mNormal;
		Vector3 mTangent;
		Vector3 mBitangent;
	*/


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

	Mesh::UnBindBuffer();
	/*
	if (interleaved)
	{
		// calculate stride from number of non-empty vertex attribute arrays
		size_t stride = 3 * sizeof(float);
		if (UV.size() > 0)         stride += 2 * sizeof(float);
		if (Normals.size() > 0)    stride += 3 * sizeof(float);
		if (Tangents.size() > 0)   stride += 3 * sizeof(float);
		if (Bitangents.size() > 0) stride += 3 * sizeof(float);

		size_t offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3 * sizeof(float);
		if (UV.size() > 0)
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 2 * sizeof(float);
		}
		if (Normals.size() > 0)
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}
		if (Tangents.size() > 0)
		{
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}
		if (Bitangents.size() > 0)
		{
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}
	}
	else
	{
		size_t offset = 0;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
		offset += Positions.size() * sizeof(float);
		if (UV.size() > 0)
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += UV.size() * sizeof(float);
		}
		if (Normals.size() > 0)
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += Normals.size() * sizeof(float);
		}
		if (Tangents.size() > 0)
		{
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += Tangents.size() * sizeof(float);
		}
		if (Bitangents.size() > 0)
		{
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += Bitangents.size() * sizeof(float);
		}
	}
	*/
	
}
