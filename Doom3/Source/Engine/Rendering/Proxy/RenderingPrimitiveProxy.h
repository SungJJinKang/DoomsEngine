#pragma once

#include <Core.h>

#include "RenderingProxy.h"

#include <array>

#include "Rendering/MaxCameraCount.h"
#include "Physics/Collider/AABB.h"
#include "Math/JINMATH/Matrix4x4.h"
#include "Rendering/Buffer/Mesh.h"

namespace dooms
{
	namespace graphics
	{
		struct FDistanceToCameraData
		{
			std::array<FLOAT32, MAX_CAMERA_COUNT> DistancesToCamera;
		};

		class RenderingPrimitiveProxy : public RenderingProxy
		{

		public:

			const graphics::Mesh* TargetMesh;
			
			bool bIsRendered = true;

			bool bIsBatched = false;

			math::Matrix4x4 ModelMatrix;

			FDistanceToCameraData DistanceToCameraData{};

			physics::AABB3D BoundingBox;

			float DesiredMaxDrawDistance;
		};
	}
}

