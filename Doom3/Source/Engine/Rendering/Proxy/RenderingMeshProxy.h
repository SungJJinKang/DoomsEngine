#pragma once
#include <Core.h>

#include <array>

#include <Rendering/Proxy/RenderingProxy.h>
#include <Rendering/Buffer/BufferID.h>
#include "Rendering/Buffer/Mesh/FMeshRawData.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include "Rendering/Buffer/eVertexArrayFlag.h"


namespace dooms
{
	namespace graphics
	{
		enum
		{
			MAX_VERTEX_BUFFER_LAYOUT_COUNT = 32
		};

		class RenderingMeshProxy : public RenderingProxy
		{
		public:

			struct FVertexBufferLayout
			{
				UINT32 mStride;
				UINT32 mOffset;
			};
			
			struct FRenderingMeshProxyInitializer
			{
				FMeshRawData MeshRawData;
				bool bDynamicWrite;
			};
			void InitRenderingMeshProxyInitializer(FRenderingMeshProxyInitializer&& Initializer) noexcept;
			
			/* You can't update buffer partially in D3D11. Use map, unmap function.
			void UpdateVertexData(const long long int dataSize, const void* data, const long long int offsetInByte) const noexcept;
			*/
			
			void Draw() const;
			void DrawArray(const INT32 startVertexLocation, const UINT32 vertexCount) const;
			void DrawArray(const GraphicsAPI::ePrimitiveType primitiveType, const INT32 startVertexLocation, const INT32 vertexCount) const;

			static UINT32 GetStride(const UINT32 VertexArrayFlag);
			
			bool IsBufferGenerated() const;
			bool IsElementBufferGenerated() const;
			
			const physics::AABB3D& GetBoundingBox() const;
			const physics::Sphere& GetBoundingSphere() const;
			
			const BufferID& GetVertexArrayObjectID() const;
			const BufferID& GetElementBufferObjectID() const;

			/**
			 * \brief You should unmap mapped buffer object before use it
			 * \param mapBufferAccessOption
			 * \return
			 */
			void* MapVertexDataBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapVertexDataBuffer();
			void* MapElementBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapElementBuffer();

			UINT64 GetNumOfIndices() const;
			UINT64 GetNumOfVertices() const;


		private:

			/**
			 * \brief only used for OPENGL
			 */
			static UINT64 BOUND_VERTEX_ARRAY_ID;

			
			/**
			 * \brief for OPENGL, Only first element is used
			 */
			static UINT64 BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT];
			/**
			 * \brief INDEX ( ELEMENT BUFFER )
			 */
			static UINT64 BOUND_INDEX_BUFFER_ID;

			/// <summary>
			/// DX11 bind this buffer
			/// </summary>
			BufferID VertexDataBuffer;
			BufferID ElementBufferObjectID;

			/// <summary>
			///	DX11 doesn't have this concept. it just bind VertexDataBuffer
			///
			/// OpenGL bind this buffer
			/// </summary>
			BufferID VertexArrayObjectID;
			UINT32 VertexArrayFlag;
			UINT32 TotalStride;
			UINT32 VertexBufferLayoutCount;
			std::array<FVertexBufferLayout, VERTEX_ARRAY_FLAG_COUNT> VertexBufferLayouts;


			FMeshRawData MeshRawData;
			bool bDynamicWrite;

			void CreateBufferObject();
			void CreateBufferObjectFromModelMesh(const FMeshRawData& MeshRawData) noexcept;


			void BindVertexArrayObject() const;
			void BindVertexBufferObject() const;
			void BindVertexBufferObject
			(
				const UINT32 bindingPosition,
				const UINT32 stride,
				const UINT32 offset
			) const;
			void BindIndexBufferObject() const;
			
			void CreateVertexArrayObjectIfNotExist();
		};
	}
}

