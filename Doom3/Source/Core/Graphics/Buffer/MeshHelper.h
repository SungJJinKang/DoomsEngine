#pragma once
#include <Core.h>

#include "Mesh.h"

namespace dooms
{
	namespace graphics
	{
		namespace meshHelper
		{
			extern Mesh* GetQuadMesh();
			extern Mesh* GetQuadMesh(const math::Vector2& leftbottom, const math::Vector2& rightup);

			enum class TriangleType
			{
				BottomFlat,
				TopFlat
			};

			extern Mesh* GetTriangleMesh(const TriangleType triangleType);
			extern Mesh* GetTriangleMesh(const TriangleType triangleType, const math::Vector2& pointA, const FLOAT32 width, const FLOAT32 height);
		}

	}
}
;

