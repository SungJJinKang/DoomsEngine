#pragma once
#include "../Core.h"

#if defined(WINDOW32) || defined(WINDOW64)
#include "Window.h"
#endif
namespace doom
{
	class OS_Server : public ISingleton<OS_Server>
	{
	private:
		 
		//Use OS::GetSingleton
#if defined(WINDOW32) || defined(WINDOW64)
		Window mWindow;
#endif
	public:

	};
}
