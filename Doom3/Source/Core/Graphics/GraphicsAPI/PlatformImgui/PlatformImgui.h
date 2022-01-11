#pragma once

#include "imgui.h"
#include "../Macros/GraphicsAPIMacros.h"

struct ImGuiContext;
namespace dooms
{
	namespace graphics
	{
		namespace PlatformImgui
		{
				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_INITIALIZEPLATFORMIMGUI)(ImGuiContext*, ImGuiMemAllocFunc, ImGuiMemFreeFunc, void*);
				DOOMS_ENGINE_GRAPHICS_API GRAPHICS_INITIALIZEPLATFORMIMGUI InitializePlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SHUTDOWNPLATFORMIMGUI)(void);
				DOOMS_ENGINE_GRAPHICS_API GRAPHICS_SHUTDOWNPLATFORMIMGUI ShutDownPlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_PRERENDERPLATFORMIMGUI)(void);
				DOOMS_ENGINE_GRAPHICS_API GRAPHICS_PRERENDERPLATFORMIMGUI PreRenderPlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_POSTRENDERPLATFORMIMGUI)(void);
				DOOMS_ENGINE_GRAPHICS_API GRAPHICS_POSTRENDERPLATFORMIMGUI PostRenderPlatformImgui;
		};
	}
}