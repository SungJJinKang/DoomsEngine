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
		/// Processor Number what Current Thread is working on
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE static unsigned long long _GetCurrentProcessorNumber();
		FORCE_INLINE static PLATFORM_HANDLE _GetCurrenThreadHandle();
		FORCE_INLINE static unsigned long long _GetCurrenThreadID();


		FORCE_INLINE static HANDLE _GetCurrenProcess();
		FORCE_INLINE static bool _SetCurrentProcessAffinityMask(const unsigned long long processAffinitMask);
		FORCE_INLINE static bool _GetCurrentProcessAffinityMask(
			unsigned long long& lpProcessAffinityMask, 
			unsigned long long& lpSystemAffinityMask
		);

		//please set mask of local processor
		//ex) first logical processor -> 1 << 0
		//ex) first logical processor and second -> (1 << 0) | (1 << 1)
		FORCE_INLINE static void _SetThreadAffinity(const PLATFORM_HANDLE threadHandle, const unsigned long long threadAffinitMask);
		FORCE_INLINE static unsigned long long _GetThreadAffinity(const PLATFORM_HANDLE threadHandle);
		
	};
}

#if defined(_WIN32) || defined(_WIN64)

#include "Window.inl"

#elif defined(__unix) || defined(__unix__)

#elif  defined(__APPLE__) || defined(__MACH__)

#else
	static_assert(false);
#endif

