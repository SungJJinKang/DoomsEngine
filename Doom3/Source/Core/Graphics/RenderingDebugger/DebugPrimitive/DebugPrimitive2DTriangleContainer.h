#pragma once

#include "DebugPrimitiveTriangleContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive2DTriangleContainer : public DebugPrimitiveTriangleContainer
		{
		public:

			bool Is3DPrimitive() const override;
		};
	}
}

