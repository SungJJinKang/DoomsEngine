#include "GraphicsAPI.h"

#include <cassert>

namespace dooms
{
	namespace graphics
	{
		DOOMS_ENGINE_GRAPHICS_API double GetTime()
		{
			assert(0);
			return 0;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphicsAPI(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
		{
			assert(0);
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeinitializeGraphicsAPI()
		{
			assert(0);
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void SwapBuffer() noexcept
		{
			assert(0);
		}
	}
}
