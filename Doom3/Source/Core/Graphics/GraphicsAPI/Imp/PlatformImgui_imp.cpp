#include "../PlatformImgui//PlatformImgui.h"

namespace dooms
{
	namespace graphics
	{
		namespace PlatformImgui
		{
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_INITIALIZEPLATFORMIMGUI InitializePlatformImgui{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SHUTDOWNPLATFORMIMGUI ShutDownPlatformImgui{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_PRERENDERPLATFORMIMGUI PreRenderPlatformImgui{nullptr};
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_POSTRENDERPLATFORMIMGUI PostRenderPlatformImgui{nullptr};
		}
	}
}