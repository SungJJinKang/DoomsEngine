#pragma once

#include "../Core.h"

namespace doom
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	class OS
	{
	public:

		//why put _ -> To prevent definition shadowing


		/// <summary>
		/// 
		/// </summary>
		/// <returns>millisecond</returns>
		FORCE_INLINE static unsigned long long _GetTickCount();
		/// <summary>
		/// sleep for milliseconds
		/// </summary>
		/// <param name="milliseconds">sleep time</param>
		FORCE_INLINE static void _Sleep(unsigned long milliseconds);
	};
}

#if defined(_WIN32) || defined(_WIN64)

#include "Window.inl"

#elif defined(__unix) || defined(__unix__)

#elif  defined(__APPLE__) || defined(__MACH__)

#else
	static_assert(false);
#endif

