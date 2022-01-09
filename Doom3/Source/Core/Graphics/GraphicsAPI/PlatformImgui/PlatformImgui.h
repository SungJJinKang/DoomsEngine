#pragma once

#include "../../Macros/DllMarcos.h"

namespace dooms
{
	namespace graphics
	{
		class DOOMS_ENGINE PlatformImgui
		{
		public:
			static void Initialize();
			static void ShutDown();
			static void PreRender();
			static void Render();
		};

		
	}
}