#pragma once

#include "DebugPrimitivePointContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive3DPointContainer : public DebugPrimitivePointContainer
		{
		public:

			bool Is3DPrimitive() const override;
		};
	}
}


