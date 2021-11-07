#pragma once

#include <Graphics/Graphics_Core.h>

namespace dooms
{
	namespace asset
	{
		class ShaderAsset;
	}

	namespace graphics
	{
		namespace OverDrawVisualization
		{
#ifdef DEBUG_DRAWER
			extern void SetOverDrawVisualizationRenderingState(const bool isSet);
			extern void ShowOverDrawVisualizationPIP(const bool isPIPDrawed);
#else
			extern void SetOverDrawVisualizationRenderingState(const bool isSet){}
			extern void ShowOverDrawVisualizationPIP(const bool isPIPDrawed){}
#endif
		};
	}
}

