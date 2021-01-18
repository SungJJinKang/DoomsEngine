#pragma once
#include "../Core.h"


struct GLFWwindow;

namespace Doom
{
	class Graphics
	{
	private:
		static GLFWwindow* Window;
	public:
		
		static int SCREEN_WIDTH, SCREEN_HEIGHT;

		
		static void Init();
		static void Loop();

	};
}
