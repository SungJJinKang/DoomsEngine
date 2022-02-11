#pragma once

#include <vector>

namespace dooms
{
	namespace graphics
	{
		class RenderingDebuggerModule;
		namespace renderingDebuggerHelper
		{
			std::vector<RenderingDebuggerModule*> CreateDefeaultRenderingDebuggerModules();
		};
	}
}

