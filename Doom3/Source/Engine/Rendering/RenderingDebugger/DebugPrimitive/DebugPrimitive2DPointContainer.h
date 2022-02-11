#pragma once

#include "DebugPrimitivePointContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive2DPointContainer : public DebugPrimitivePointContainer
		{
		public:

			bool Is3DPrimitive() const override;
		};
	}
}

