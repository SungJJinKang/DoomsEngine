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
				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_INITIALIZEPLATFORMIMGUI)(void* platformWindow, const char* apiVersion, ImGuiContext*, ImGuiMemAllocFunc, ImGuiMemFreeFunc, void*);
				extern GRAPHICS_INITIALIZEPLATFORMIMGUI InitializePlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SHUTDOWNPLATFORMIMGUI)(void);
				extern GRAPHICS_SHUTDOWNPLATFORMIMGUI ShutDownPlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_PRERENDERPLATFORMIMGUI)(void);
				extern GRAPHICS_PRERENDERPLATFORMIMGUI PreRenderPlatformImgui;


				typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_POSTRENDERPLATFORMIMGUI)(void);
				extern GRAPHICS_POSTRENDERPLATFORMIMGUI PostRenderPlatformImgui;
		};
	}
}