#pragma once


#include "DebugPrimitiveTriangleContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive3DTriangleContainer : public DebugPrimitiveTriangleContainer
		{

		public:

			bool Is3DPrimitive() const override;

		};
	}
}


