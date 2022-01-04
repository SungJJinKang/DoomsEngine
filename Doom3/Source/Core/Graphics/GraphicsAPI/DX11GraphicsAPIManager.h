#pragma once
#include <Core.h>

#include "GraphicsAPIManager.h"

namespace dooms
{
	namespace graphics
	{
		class DX11GraphicsAPIManager : public GraphicsAPIManager
		{
		public:
			void Initialize() override;
			void DeInitialize() override;
		};
	}
}

