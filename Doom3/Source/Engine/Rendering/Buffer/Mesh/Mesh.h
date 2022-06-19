#pragma once
#include <Core.h>

#include <array>

#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Graphics/GraphicsAPI/Manager/GraphicsAPIManager.h>
#include <Rendering/Buffer/BufferID.h>

#include "Mesh.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Graphics_Server;
		class RenderingMeshProxy;
		class DOOM_API D_CLASS Mesh : public DObject
		{
			//GENERATE_BODY()
			
		private:

			RenderingMeshProxy* MeshProxy = nullptr;

			UINT64 DataComponentCount;
			UINT64 VertexCount;
			std::vector<UINT8> MeshRawData;
			GraphicsAPI::ePrimitiveType PrimitiveType;
			UINT32 VertexArrayFlag;
			std::vector<UINT32> IndiceList;
			bool DynamicWrite;
			
			/// <summary>
			/// this is local coordinate, you should map to your world coordinate
			/// </summary>
			physics::AABB3D mAABB3D{nullptr};
			physics::Sphere mSphere{nullptr};

			void OnSetPendingKill() override;
			
	
		public:

			void CreateRenderingMeshProxy();
			void DestroyRenderingMeshProxy();
			RenderingMeshProxy* GetRenderingMeshProxy() const;
			bool IsRenderingMeshProxyCreated() const;

			Mesh();
			virtual ~Mesh() override;
			
			Mesh
			(
				const UINT64 DataComponentCount,
				const UINT64 VertexCount,
				const std::vector<UINT8> MeshRawData, 
				const GraphicsAPI::ePrimitiveType PrimitiveType,
				const UINT32 VertexArrayFlag,
				const std::vector<UINT32> IndiceList,
				const bool DynamicWrite
			);
			Mesh(const ThreeDModelMesh& ThreeDModelMesh);
			Mesh& operator=(const ThreeDModelMesh& threeDModelMesh);

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;

			const ThreeDModelMesh* GetTargetThreeDModelMesh() const;
			void DestroyUniformBufferProxy() final;
			
			void CreateBufferObjectFromModelMesh(const ThreeDModelMesh& threeDModelMesh) noexcept;

			
			const physics::AABB3D& GetBoundingBox() const;
			const physics::Sphere& GetBoundingSphere() const;
			
			/**
			 * \brief You should unmap mapped buffer object before use it 
			 * \param mapBufferAccessOption 
			 * \return 
			 */
			void* MapVertexDataBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapVertexDataBuffer();
			void* MapElementBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapElementBuffer();
		};
	}
}