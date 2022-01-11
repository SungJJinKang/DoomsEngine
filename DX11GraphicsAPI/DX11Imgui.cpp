#include "PlatformImgui/PlatformImgui.h"

#include <cassert>

namespace dooms
{
	namespace input
	{
		DOOMS_ENGINE_GRAPHICS_API bool InitializePlatformImgui(ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data)
		{
			assert(false);

			return false;
		}

		DOOMS_ENGINE_GRAPHICS_API bool ShutDownPlatformImgui()
		{
			assert(false);

			return false;
		}

		DOOMS_ENGINE_GRAPHICS_API void PreRenderPlatformImgui()
		{
			assert(false);
		}

		DOOMS_ENGINE_GRAPHICS_API void PostRenderPlatformImgui()
		{
			assert(false);
		}
	}
}