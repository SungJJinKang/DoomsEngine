#pragma once

#include <Core.h>

#if defined(_WIN32) || defined(_WIN64)

#include <Windows.h>

#ifndef PLATFORM_HANDLE
#define PLATFORM_HANDLE HANDLE
#endif

#ifndef PLATFORM_INVALID_HANDLE_CONSTANT
#define PLATFORM_INVALID_HANDLE_CONSTANT INVALID_HANDLE_VALUE 
#endif

#elif defined(__unix) || defined(__unix__)

#elif  defined(__APPLE__) || defined(__MACH__)

#else
static_assert(false);
#endif




namespace doom
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	class os
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
		FORCE_INLINE static void _Sleep(const unsigned long milliseconds);

		/// <summary>
		/// Processor Number of Current Thread
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE static unsigned int _GetCurrentProcessorNumber();
		FORCE_INLINE static PLATFORM_HANDLE _GetCurrenThreadHandle();
		FORCE_INLINE static unsigned int _GetCurrenThreadID();


		FORCE_INLINE static HANDLE _GetCurrenProcess();
		FORCE_INLINE static bool _SetProcessAffinityMask(const unsigned long long processAffinitMask);

		FORCE_INLINE static void _SetThreadAffinity(const PLATFORM_HANDLE threadHandle, const unsigned long long threadAffinitMask);
		
		FORCE_INLINE static unsigned long long _GetCurrentThreadAffinity(const PLATFORM_HANDLE threadHandle);
		
	};
}

#if defined(_WIN32) || defined(_WIN64)

#include "Window.inl"

#elif defined(__unix) || defined(__unix__)

#elif  defined(__APPLE__) || defined(__MACH__)

#else
	static_assert(false);
#endif

