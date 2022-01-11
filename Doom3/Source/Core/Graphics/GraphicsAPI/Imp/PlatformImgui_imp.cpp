#include "../PlatformImgui//PlatformImgui.h"

namespace dooms
{
	namespace graphics
	{
		namespace PlatformImgui
		{
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_INITIALIZEPLATFORMIMGUI InitializePlatformImgui;
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SHUTDOWNPLATFORMIMGUI ShutDownPlatformImgui;
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_PRERENDERPLATFORMIMGUI PreRenderPlatformImgui;
			DOOMS_ENGINE_GRAPHICS_API GRAPHICS_POSTRENDERPLATFORMIMGUI PostRenderPlatformImgui;
		}
	}
}