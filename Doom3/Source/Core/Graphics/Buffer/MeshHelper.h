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
		}

	}
}
;

