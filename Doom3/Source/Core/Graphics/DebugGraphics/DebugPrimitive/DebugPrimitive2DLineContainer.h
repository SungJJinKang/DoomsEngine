#pragma once


#include "DebugPrimitiveLineContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitive2DLineContainer : public DebugPrimitiveLineContainer
		{
		public:

			bool Is3DPrimitive() const override;
		};
	}
}

