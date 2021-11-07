#pragma once
#include "Buffer.h"

#include <memory>
#include "../OverlapBindChecker.h"
#include "../ePrimitiveType.h"
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>

#include "../GraphicsAPI.h"
#include <Vector2.h>

namespace dooms
{

	struct ThreeDModelMesh;

	namespace graphics
	{
		class Graphics_Server;
		class Mesh : public Buffer
		{
			DOBJECT_CLASS_BODY(Mesh, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(Buffer)

			friend class Graphics_Server;
			friend class DebugDrawer;

		public:

			static inline const char VERTEX_ARRAY_TAG[]{ "VERTEX_ARRAY" };
			static inline const char VERTEX_BUFFER_TAG[]{ "VERTEX_BUFFER" };
			static inline const char INDEX_BUFFER_TAG[]{ "INDEX_BUFFER" };

		private:

			enum eVertexArrayFlag : UINT32
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
			//UINT32 mVertexBufferObject; <- Use Buffer::data

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			INT32 mNumOfIndices;
			INT32 mNumOfVertices;
			ePrimitiveType mPrimitiveType;

			UINT32 mVertexArrayFlag;

			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			FORCE_INLINE void BindBuffer() const noexcept final
			{
				D_ASSERT(mVertexArrayObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_ARRAY_TAG, mVertexArrayObjectID))
				{
					glBindVertexArray(mVertexArrayObjectID);
				}
			}

			FORCE_INLINE void BindElementBuffer() const noexcept
			{
				D_ASSERT(mElementBufferObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(INDEX_BUFFER_TAG, mElementBufferObjectID))
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObjectID);
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
			
			Mesh(GLsizeiptr dataCount, const void* data, ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept;
			Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
			Mesh& operator=(const ThreeDModelMesh& threeDModelMesh) noexcept;

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;
			
			FORCE_INLINE void BindVertexArrayObject() const noexcept
			{
				BindBuffer();
			}
			FORCE_INLINE void UnBindBuffer() const noexcept final
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_ARRAY_TAG, 0))
				{
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
			void BufferData(GLsizeiptr dataComponentCount, const void* data, ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept;
			void BufferSubData(GLsizeiptr dataComponentCount, const void* data, khronos_intptr_t offsetInByte) const noexcept;
			void BindVertexBufferObject() const;
			void BufferDataFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
			FORCE_INLINE void Draw() const
			{
				D_ASSERT(mPrimitiveType != ePrimitiveType::NONE);

				BindVertexArrayObject();
				if (IsElementBufferGenerated() == true)
				{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
					// you don't need bind EBO everytime, EBO will be bound automatically when bind VAO
					GraphicsAPI::DrawElement(mPrimitiveType, mNumOfIndices, GL_UNSIGNED_INT, 0);
				}
				else
				{
					GraphicsAPI::DrawArray(mPrimitiveType, 0, mNumOfVertices);
				}
			}
			FORCE_INLINE void DrawArray(const INT32 startIndexInComponent, const UINT32 vertexCount) const
			{
				D_ASSERT(mPrimitiveType != ePrimitiveType::NONE);

				BindVertexArrayObject();

				GraphicsAPI::DrawArray(mPrimitiveType, startIndexInComponent, vertexCount);
			}

			FORCE_INLINE void DrawArray(const ePrimitiveType primitiveType, const INT32 startVertexIndex, const INT32 vertexCount) const
			{
				D_ASSERT(primitiveType != ePrimitiveType::NONE);

				BindVertexArrayObject();

				GraphicsAPI::DrawArray(primitiveType, startVertexIndex, vertexCount);
			}

			static constexpr UINT32 GetStride(const UINT32 vertexArrayFlag);

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

			virtual bool IsBufferGenerated() const final;
			FORCE_INLINE bool IsElementBufferGenerated() const 
			{
				return mElementBufferObjectID.IsValid();
			}

			void UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount);


			const physics::AABB3D& GetBoundingBox() const;
			const physics::Sphere& GetBoundingSphere() const;

			UINT32 GetVertexArrayObjectID() const;
			UINT32 GetElementBufferObjectID() const;
		};
	}
}