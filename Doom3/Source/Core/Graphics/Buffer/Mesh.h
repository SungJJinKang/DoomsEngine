#pragma once
#include "Buffer.h"

#include <functional>
#include "../../Asset/ThreeDModelAsset.h"
#include "../../OverlapBindChecker/OverlapBindChecker.h"

namespace doom
{
	namespace graphics
	{
		class Mesh : public Buffer
		{
		private:
			unsigned int mVertexArrayObject;
			unsigned int& mVertexBufferObject = this->mBufferID;
			unsigned int mElementBufferObject;

			const std::reference_wrapper<const ThreeDModelMesh> mThreeDModelMesh;
			unsigned int mNumOfIndices;
			unsigned int mNumOfVertices;
			ePrimitiveType mPrimitiveType;
		public:
			Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept
				: Buffer(), mThreeDModelMesh{ threeDModelMesh }, mVertexArrayObject{}, mElementBufferObject{}, mNumOfVertices{ 0 }, mNumOfIndices{ 0 }
			{
				glGenVertexArrays(1, &(this->mVertexArrayObject));

				if (threeDModelMesh.bHasIndices)
				{
					glGenBuffers(1, &(this->mElementBufferObject));
				}

				this->BufferDataFromModelMesh();
			}

			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			void BindBuffer() noexcept final
			{
				D_CHECK_OVERLAP_BIND("VertexArray", this->mVertexArrayObject);
				glBindVertexArray(this->mVertexArrayObject);
			}
			void UnBindBuffer() noexcept final
			{
				glBindVertexArray(0);
			}

			/// <summary>
			/// layout(location = 0) in vec3 aPos;
			/// layout(location = 1) in vec2 aUV0;
			/// layout(location = 2) in vec3 aNormal;
			/// layout(location = 3) in vec3 aTangent;
			/// layout(location = 4) in vec3 aBitangent;
			/// 
			/// above datas should be arranged sequentially
			/// 
			/// aPos(0)  aUV0  aNormal  aTangent  aBitangent
			/// 
			/// </summary>
			/// <param name="size"></param>
			/// <param name="data"></param>
			void BufferData(GLsizeiptr size, const void* data) noexcept final;
			void BufferDataFromModelMesh() noexcept;
			void Draw()
			{
				this->BindBuffer();
				if (mNumOfIndices > 0)
				{
					glDrawElements(GL_TRIANGLES, this->mNumOfIndices, GL_UNSIGNED_INT, 0);
				}
				else
				{
					glDrawArrays(static_cast<unsigned int>(this->mPrimitiveType), 0, this->mNumOfVertices);
				}
			}
		};
	}
}