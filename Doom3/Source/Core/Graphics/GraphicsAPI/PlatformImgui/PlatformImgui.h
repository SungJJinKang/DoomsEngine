#pragma once

#include "../../Macros/DllMarcos.h"

struct ImGuiContext;
namespace dooms
{
	namespace graphics
	{
		class DOOMS_ENGINE PlatformImgui
		{
		public:
			static ImGuiContext* Initialize();
			static void ShutDown();
			static void PreRender();
			static void Render();
			static void PostRender();
		};

		
	}
}