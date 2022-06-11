#pragma once

#include <Core.h>

#include "RenderingProxy.h"

#include <array>

#include "Rendering/MaxCameraCount.h"
#include "Physics/Collider/AABB.h"
#include "Math/JINMATH/Matrix4x4.h"
#include "Rendering/Buffer/Mesh.h"
#include <Rendering/Culling/EveryCulling/DataType/EntityBlockViewer.h>

namespace dooms
{
	namespace graphics
	{
		class Material;
		struct FDistanceToCameraData
		{
			std::array<FLOAT32, MAX_CAMERA_COUNT> DistancesToCamera;
		};

		class RenderingPrimitiveProxy : public RenderingProxy
		{

		public:
			
			bool bIsRendered = true;
			bool bIsBatched = false;

			const graphics::Mesh* TargetMesh;

			math::Matrix4x4 ModelMatrix;
			
			physics::AABB3D BoundingBox;

			FDistanceToCameraData DistanceToCameraData{};
			float DesiredMaxDrawDistance;

			graphics::Material* TargetMaterial;

			culling::EntityBlockViewer CullingEntityBlockViewer;
		};
	}
}

