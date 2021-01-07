#pragma once
#include "../Log/Debug.h"
#include "../API/OpenglAPI.h"

namespace Doom
{
	class Graphics
	{
	private:
		static GLFWwindow* Window;
	public:
		
		static int SCREEN_WIDTH, SCREEN_HEIGHT;

		
		static void Init();


	};
}
