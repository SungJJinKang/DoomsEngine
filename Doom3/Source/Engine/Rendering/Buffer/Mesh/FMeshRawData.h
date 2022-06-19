#pragma once

#include <Core.h>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Vector3.h>
#include <Collider/AABB.h>
#include <Collider/Sphere.h>

namespace dooms
{
	namespace graphics
	{
		/// <summary>
		/// layout(location = 0) in vec3 aPos;
		/// layout(location = 1) in vec2 aUV0;
		/// layout(location = 2) in vec3 aNormal;
		/// layout(location = 3) in vec3 aTangent;
		/// layout(location = 4) in vec3 aBitangent;
		/// 
		/// Never edit this struct, Never change placement order of datas
		/// </summary>
		struct FMeshRawData
		{
			bool bIsValidMesh;

			UINT64 VerticeCount;
			char* Data;
			math::Vector3* Vertex;
			math::Vector3* TexCoord; //support only one channel
			math::Vector3* Normal;
			math::Vector3* Tangent;
			math::Vector3* mBitangent;
			
			graphics::GraphicsAPI::ePrimitiveType PrimitiveType;

			bool bHasIndices;
			std::vector<UINT32> MeshIndices;

			UINT32 VerticeStride;
			UINT32 VertexArrayFlag;

			physics::AABB3D BoundingBox{ nullptr };
			physics::Sphere BoundingSphere{ nullptr };

			FMeshRawData();
			FMeshRawData(const size_t VerticeCount);
			FMeshRawData(const FMeshRawData&);
			FMeshRawData(FMeshRawData&&) noexcept;
			FMeshRawData& operator=(const FMeshRawData&);
			FMeshRawData& operator=(FMeshRawData&&) noexcept;
			~FMeshRawData();

			void Allocate(const size_t verticeCount);
			unsigned long long GetAllocatedDataSize() const;
			void Free();
		};
	}
}

