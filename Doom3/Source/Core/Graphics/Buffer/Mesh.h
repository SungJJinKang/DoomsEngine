#pragma once
#include "Buffer.h"

#include <functional>
#include <memory>
#include "../OverlapBindChecker.h"
#include "../ePrimitiveType.h"
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

#include "../GraphicsAPI.h"
#include <Vector2.h>

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

		public:

			static inline const char* VERTEX_ARRAY_TAG{ "VERTEX_ARRAY" };
			static inline const char* VERTEX_BUFFER_TAG{ "VERTEX_BUFFER" };

		private:

			enum eVertexArrayFlag : unsigned int
			{
				None = 0x0,
				VertexVector3 =  1,
				VertexVector2 =  2,
				TexCoord = 4,
				mNormal = 8,
				mTangent = 16,
				mBitangent = 32,
			};

			BufferID mVertexArrayObjectID;
			BufferID mElementBufferObjectID;
			//unsigned int mVertexBufferObject; <- Use Buffer::data

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			int mNumOfIndices;
			int mNumOfVertices;
			ePrimitiveType mPrimitiveType;

			unsigned int mVertexArrayFlag;

			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			FORCE_INLINE void BindBuffer() noexcept final
			{
				D_ASSERT(this->mVertexArrayObjectID != 0);

				if (OverlapBindChecker::GetBoundID(VERTEX_ARRAY_TAG) != this->mVertexArrayObjectID)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(VERTEX_ARRAY_TAG, this->mVertexArrayObjectID);
					glBindVertexArray(this->mVertexArrayObjectID);
				}
			}

			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			physics::AABB3D mAABB3D;
			physics::Sphere mSphere;

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
			
			FORCE_INLINE void BindVertexArrayObject() noexcept
			{
				this->BindBuffer();
			}
			FORCE_INLINE void UnBindBuffer() noexcept final
			{
				if (OverlapBindChecker::GetBoundID(VERTEX_ARRAY_TAG) != 0)
				{
					D_CHECK_OVERLAP_BIND_AND_SAVE_BIND(VERTEX_ARRAY_TAG, 0);
					glBindVertexArray(0);
				}
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
			FORCE_INLINE void Draw()
			{
				D_ASSERT(this->mPrimitiveType != ePrimitiveType::NONE);

				this->BindVertexArrayObject();
				if (mNumOfIndices > 0)
				{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
					// you don't need bind mVertexArrayObjectID everytime, EBO will be bound automatically when bind VAO
					GraphicsAPI::DrawElement(this->mPrimitiveType, this->mNumOfIndices, GL_UNSIGNED_INT, 0);
				}
				else
				{
					GraphicsAPI::DrawArray(this->mPrimitiveType, 0, this->mNumOfVertices);
				}
			}
			FORCE_INLINE void DrawArray(int startIndexInComponent, unsigned int vertexCount)
			{
				D_ASSERT(this->mPrimitiveType != ePrimitiveType::NONE);

				this->BindVertexArrayObject();

				GraphicsAPI::DrawArray(this->mPrimitiveType, startIndexInComponent, vertexCount);
			}

			FORCE_INLINE void DrawArray(ePrimitiveType primitiveType, int startVertexIndex, int vertexCount)
			{
				D_ASSERT(primitiveType != ePrimitiveType::NONE);

				this->BindVertexArrayObject();

				GraphicsAPI::DrawArray(primitiveType, startVertexIndex, vertexCount);
			}

			static constexpr unsigned int GetStride(unsigned int vertexArrayFlag);

			static inline std::shared_ptr<Mesh> QuadMesh{};
			static std::shared_ptr<Mesh> GetQuadMesh();
			/// <summary>
			/// If you want mesh for postprocessin or ren
			/// If you want mesh for postprocessin or rendering 2d quad on screen
			/// </summary>
			/// <param name="leftbottom"></param>
			/// <param name="rightup"></param>
			/// <returns></returns>
			static Mesh GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup);

			virtual bool IsBufferGenerated() final;

			const physics::AABB3D& GetAABB() const;
			physics::AABB3D GetAABB();

			const physics::Sphere& GetSphere() const;
			physics::Sphere GetSphere();

			unsigned int GetVertexArrayObjectID();
			unsigned int GetElementBufferObjectID();
		};
	}
}