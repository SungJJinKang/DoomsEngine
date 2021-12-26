#pragma once

#include "DebugPrimitiveLineContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive3DLineContainer : public DebugPrimitiveLineContainer
		{
		public:

			bool Is3DPrimitive() const override;
		};
	}
}


