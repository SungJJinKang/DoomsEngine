#pragma once

#include "imgui.h"
#include "../../Macros/DllMarcos.h"

struct ImGuiContext;
namespace dooms
{
	namespace graphics
	{
		class DOOMS_ENGINE PlatformImgui
		{
		public:
			
			static bool Initialize(ImGuiContext* const imGuiContext, ImGuiMemAllocFunc p_alloc_func, ImGuiMemFreeFunc p_free_func, void* p_user_data);
			static bool ShutDown();
			static void PreRender();
			static void PostRender();
		};

		
	}
}