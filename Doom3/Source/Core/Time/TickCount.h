#pragma once

#include "../Core.h"

#if defined(WINDOW32) || defined(WINDOW64)
#include <Windows.h>
#endif


namespace doom
{
	namespace time
	{

		class TickCount
		{

		public:
			static unsigned long long GetTickCount()
			{
#if defined(WINDOW32)
				return GetTickCount();
#elif defined(WINDOW64)
				return GetTickCount64();
#endif

			}

		};

	}
}