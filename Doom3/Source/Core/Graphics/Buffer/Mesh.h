#pragma once
#include "Buffer.h"

#include <functional>
#include "../OverlapBindChecker.h"
#include "../Asset/ePrimitiveType.h"

namespace doom
{

	struct ThreeDModelMesh;

	namespace graphics
	{
		class Mesh : public Buffer
		{
			enum eVertexArrayFlag : unsigned int
			{
				None = 0x0,
				Vertex = 1 < 0,
				TexCoord = 1 < 1,
				mNormal = 1 < 2,
				mTangent = 1 < 3,
				mBitangent = 1 < 4,
			};


		private:
			unsigned int mVertexArrayObject;
			unsigned int& mVertexBufferObject = this->mBufferID;
			unsigned int mElementBufferObject;

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			unsigned int mNumOfIndices;
			unsigned int mNumOfVertices;
			ePrimitiveType mPrimitiveType;

		protected:
			void GenMeshBuffer(bool hasIndice);
			void DeleteBuffers() final;
		public:
			Mesh();
			virtual ~Mesh();
			
			Mesh(GLsizeiptr dataCount, const void* data, unsigned int vertexArrayFlag) noexcept;
			Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
			Mesh& operator=(const ThreeDModelMesh& threeDModelMesh) noexcept;

			Mesh(Mesh&& mesh) noexcept;
			Mesh& operator=(Mesh&& mesh) noexcept;

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

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
			/// <param name="size">size of data in byte</param>
			/// <param name="data"></param>
			void BufferData(GLsizeiptr dataCount, const void* data, unsigned int vertexArrayFlag) noexcept;
			void BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
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

			static constexpr unsigned int GetStride(unsigned int vertexArrayFlag);

			static inline Mesh* QuadMesh{ nullptr };
			static const Mesh& GetQuadMesh();
		};
	}
}