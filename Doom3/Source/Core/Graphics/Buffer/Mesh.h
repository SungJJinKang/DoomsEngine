#pragma once
#include "Buffer.h"

#include <functional>
#include <memory>
#include "../OverlapBindChecker.h"
#include "../ePrimitiveType.h"
#include <Physics/AABB.h>

namespace doom
{

	struct ThreeDModelMesh;

	namespace graphics
	{
		class Graphics_Server;
		class Mesh : protected Buffer
		{
			friend class Graphics_Server;
			friend class DebugGraphics;
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
			BufferID mVertexArrayObjectID;
			BufferID mElementBufferObjectID;
			//unsigned int mVertexBufferObject; <- Use Buffer::data

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			unsigned int mNumOfIndices;
			unsigned int mNumOfVertices;
			ePrimitiveType mPrimitiveType;

			unsigned int mVertexArrayFlag;

			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			void BindBuffer() noexcept final
			{
				D_ASSERT(this->mVertexArrayObjectID != 0);
				D_CHECK_OVERLAP_BIND("VertexArrayObject", this->mVertexArrayObjectID);
				glBindVertexArray(this->mVertexArrayObjectID);
			}

			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			physics::AABB3D mAABB3D;

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

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;
			
			void BindVertexArrayObject() noexcept
			{
				this->BindBuffer();
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
			/// <param name="vertexArrayFlag">use eVertexArrayFlag!!!! </param>
			/// <returns></returns>
			void BufferData(GLsizeiptr dataComponentCount, const void* data, ePrimitiveType primitiveType, unsigned int vertexArrayFlag) noexcept;
			void BufferSubData(GLsizeiptr dataComponentCount, const void* data, khronos_intptr_t offsetInByte) noexcept;
			void BindVertexBufferObject();
			void BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
			void Draw()
			{
				D_ASSERT(this->mPrimitiveType != ePrimitiveType::NONE);

				this->BindVertexArrayObject();
				if (mNumOfIndices > 0)
				{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
					// you don't need bind mVertexArrayObjectID everytime, EBO will be bound automatically when bind VAO
					glDrawElements(static_cast<unsigned int>(this->mPrimitiveType), this->mNumOfIndices, GL_UNSIGNED_INT, 0);
				}
				else
				{
					glDrawArrays(static_cast<unsigned int>(this->mPrimitiveType), 0, this->mNumOfVertices);
				}
			}
			void DrawArray(int startIndexInComponent, unsigned int vertexCount)
			{
				D_ASSERT(this->mPrimitiveType != ePrimitiveType::NONE);

				glDrawArrays(static_cast<unsigned int>(this->mPrimitiveType), startIndexInComponent, vertexCount);
			}

			void DrawArray(ePrimitiveType primitiveType, int startIndexInComponent, unsigned int vertexCount)
			{
				D_ASSERT(primitiveType != ePrimitiveType::NONE);

				glDrawArrays(static_cast<unsigned int>(primitiveType), startIndexInComponent, vertexCount);
			}

			static constexpr unsigned int GetStride(unsigned int vertexArrayFlag);

			static inline std::shared_ptr<Mesh> QuadMesh{};
			static std::shared_ptr<Mesh> GetQuadMesh();

			virtual bool IsBufferGenerated() final;

			const physics::AABB3D& GetAABB() const;
			physics::AABB3D GetAABB();


		};
	}
}