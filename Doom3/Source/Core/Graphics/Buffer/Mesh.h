#pragma once
#include "Buffer.h"

#include <memory>
#include "../OverlapBindChecker.h"
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include "eVertexArrayFlag.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Vector2.h>

#include "Mesh.reflection.h"
namespace dooms
{

	class ThreeDModelMesh;

	namespace graphics
	{
		class Graphics_Server;
		class DOOM_API D_CLASS Mesh : public Buffer
		{
			GENERATE_BODY()
			
		public:

			

			static inline const char VERTEX_ARRAY_TAG[]{ "VERTEX_ARRAY" };
			static inline const char VERTEX_BUFFER_TAG[]{ "VERTEX_BUFFER" };
			static inline const char INDEX_BUFFER_TAG[]{ "INDEX_BUFFER" };

		private:

			D_PROPERTY()
			const ThreeDModelMesh* mTargetThreeDModelMesh;

			/// <summary>
			/// DX11 bind this buffer
			/// </summary>
			D_PROPERTY()
			BufferID mVertexDataBuffer;

			D_PROPERTY()
			BufferID mElementBufferObjectID;	

			/// <summary>
			///	DX11 doesn't have this concept. it just bind VertexDataBuffer
			///
			/// OpenGL bind this buffer
			/// </summary>
			D_PROPERTY()
			BufferID mVertexArrayObjectID;
		
			//UINT32 mVertexBufferObject; <- Use Buffer::data

			//const ThreeDModelMesh* mThreeDModelMesh; don't save ModelMeshAssetData
			D_PROPERTY()
			UINT64 mNumOfIndices;
			D_PROPERTY()
			UINT64 mNumOfVertices;
			D_PROPERTY()
			GraphicsAPI::ePrimitiveType mPrimitiveType;

			D_PROPERTY()
			UINT32 mVertexArrayFlag;

			/// <summary>
			/// bind buffer array object
			/// </summary>
			/// <returns></returns>
			D_FUNCTION()
			FORCE_INLINE void BindBuffer() const noexcept final
			{
				D_ASSERT(mVertexArrayObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(VERTEX_ARRAY_TAG, mVertexArrayObjectID))
				{
					GraphicsAPI::BindVertexArrayObject(mVertexArrayObjectID);
				}
			}

			D_FUNCTION()
			FORCE_INLINE void BindElementBuffer() const noexcept
			{
				D_ASSERT(mElementBufferObjectID.IsValid());

				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(INDEX_BUFFER_TAG, mElementBufferObjectID))
				{
					GraphicsAPI::BindIndexBufferObject(mElementBufferObjectID);
				}
			}

			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			D_PROPERTY()
			physics::AABB3D mAABB3D{math::Vector4{-1.0f}, math::Vector4{1.0f}};
			D_PROPERTY()
			physics::Sphere mSphere{math::Vector3{0.0f}, 1.0f};

			void OnSetPendingKill() override;

			void BindVertexArrayObject() const;
			void BindVertexBufferObject() const;
			void BindVertexBufferObject(const UINT32 bindingPosition, const graphics::GraphicsAPI::eGraphicsPipeLineStage graphicsPipeLineStage) const;

			void CreateVertexArrayObjectIfNotExist();

	
		public:

			

			Mesh();
			virtual ~Mesh();
			
			Mesh(const long long int dataCount, const void* data, GraphicsAPI::ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept;
			Mesh(const ThreeDModelMesh& threeDModelMesh) noexcept;
			Mesh& operator=(const ThreeDModelMesh& threeDModelMesh) noexcept;

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;

			const ThreeDModelMesh* GetTargetThreeDModelMesh() const;
			void DeleteBuffers() final;

			
			void CreateBufferObject(const long long int dataComponentCount, const void* data, GraphicsAPI::ePrimitiveType primitiveType, UINT32 vertexArrayFlag) noexcept;
			void CreateBufferObjectFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;

			void UpdateVertexData(const long long int dataComponentCount, const void* data, const long long int offsetInByte) const noexcept;


			FORCE_INLINE void Draw() const
			{
				D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

				BindVertexArrayObject();
				if (IsElementBufferGenerated() == true)
				{// TODO : WHY THIS MAKE ERROR ON RADEON GPU, CHECK THIS https://stackoverflow.com/questions/18299646/gldrawelements-emits-gl-invalid-operation-when-using-amd-driver-on-linux
					// you don't need bind EBO everytime, EBO will be bound automatically when bind VAO
					GraphicsAPI::DrawIndexed(mPrimitiveType, mNumOfIndices);
				}
				else
				{
					GraphicsAPI::Draw(mPrimitiveType, 0, mNumOfVertices);
				}
			}
			FORCE_INLINE void DrawArray(const INT32 startVertexLocation, const UINT32 vertexCount) const
			{
				D_ASSERT(mPrimitiveType != GraphicsAPI::ePrimitiveType::NONE);

				BindVertexArrayObject();

				GraphicsAPI::Draw(mPrimitiveType, vertexCount, startVertexLocation);
			}

			FORCE_INLINE void DrawArray(const GraphicsAPI::ePrimitiveType primitiveType, const INT32 startVertexLocation, const INT32 vertexCount) const
			{
				D_ASSERT(primitiveType != GraphicsAPI::ePrimitiveType::NONE);

				BindVertexArrayObject();

				GraphicsAPI::Draw(primitiveType, vertexCount, startVertexLocation);
			}

			static constexpr UINT32 GetStride(const UINT32 vertexArrayFlag);

			

			D_FUNCTION()
			virtual bool IsBufferGenerated() const final;

			D_FUNCTION()
			FORCE_INLINE bool IsElementBufferGenerated() const 
			{
				return mElementBufferObjectID.IsValid();
			}

			D_FUNCTION()
			void UpdateElementBuffer(const UINT32* indices, const UINT32 indiceCount);


			D_FUNCTION()
			const physics::AABB3D& GetBoundingBox() const;
			D_FUNCTION()
			const physics::Sphere& GetBoundingSphere() const;

			D_FUNCTION()
			const BufferID& GetVertexArrayObjectID() const;
			D_FUNCTION()
			const BufferID& GetElementBufferObjectID() const;

			/**
			 * \brief You should unmap mapped buffer object before use it 
			 * \param mapBufferAccessOption 
			 * \return 
			 */
			void* GetMappedVertexArrayObject(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapMappedVertexArrayObject();
			void* GetMappedElementBufferObjectObject(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapMappedElementBufferObjectObject();
		};
	}
}