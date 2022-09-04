#pragma once
#include <Core.h>

#include <array>

#include <Physics/Collider/AABB.h>
#include <Physics/Collider/Sphere.h>
#include <Rendering/Buffer/Mesh/FMeshRawData.h>
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

			FMeshRawData MeshRawData;
			bool DynamicWrite;
			
			void OnSetPendingKill() override;
			
	
		public:

			void CreateRenderingMeshProxy();
			void DestroyRenderingMeshProxy();
			RenderingMeshProxy* GetRenderingMeshProxy() const;
			bool IsRenderingMeshProxyCreated() const;

			Mesh();
			virtual ~Mesh() override;
			
			Mesh(const graphics::FMeshRawData& InMeshRawData);
			Mesh(graphics::FMeshRawData&& InMeshRawData) noexcept;
			Mesh& operator=(const graphics::FMeshRawData& InMeshData);
			Mesh& operator=(graphics::FMeshRawData&& InMeshData) noexcept;

			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			Mesh(Mesh&&) noexcept = default;
			Mesh& operator=(Mesh&&) noexcept = default;

			const graphics::FMeshRawData& GetMeshRawData() const;

			const physics::AABB3D& GetBoundingBox() const;
			const physics::Sphere& GetBoundingSphere() const;
			
			/*void* MapVertexDataBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapVertexDataBuffer();
			void* MapElementBuffer(const dooms::graphics::GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption);
			void UnmapElementBuffer();*/

			UINT64 GetNumOfIndices() const;
			UINT64 GetNumOfVertices() const;

		};
	}
}