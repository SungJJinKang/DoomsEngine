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
		class Graphics_Server;
		class Mesh : public Buffer
		{
			friend class Graphics_Server;
		private:

			enum eVertexArrayFlag : unsigned int
			{
				None = 0x0,
				Vertex =  1,
				TexCoord = 2,
				mNormal = 4,
				mTangent = 8,
				mBitangent = 16,
			};


		private:
			unsigned int mVertexArrayObject;
			unsigned int mElementBufferObject;
			//unsigned int mVertexBufferObject; <- Use Buffer::mBufferID

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			unsigned int mNumOfIndices;
			unsigned int mNumOfVertices;
			ePrimitiveType mPrimitiveType;

		protected:
			void GenMeshBuffer(bool hasIndice);
			void DeleteBuffers() final;
			virtual void GenBufferIfNotGened(bool hasIndice) final;
		public:
			Mesh();
			virtual ~Mesh();
			
			Mesh(GLsizeiptr dataCount, const void* data, ePrimitiveType primitiveType, unsigned int vertexArrayFlag) noexcept;
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
				D_ASSERT(this->mVertexArrayObject != 0);
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
			/// <param name="dataCount">count of data, vec3 -> 3 </param>
			/// <param name="data">first element address of data array's element</param>
			/// <param name="primitiveType"></param>
			/// <param name="vertexArrayFlag"></param>
			/// <returns></returns>
			void BufferData(GLsizeiptr dataCount, const void* data, ePrimitiveType primitiveType, unsigned int vertexArrayFlag) noexcept;
			void BindVertexBufferObject();
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

			virtual bool IsBufferGenerated() final;

		};
	}
}