#pragma once

#include <Core.h>

#ifdef _WIN64

#define OS_WIN64

#elif _WIN32

#define OS_WIN32

#elif defined(__unix) || defined(__unix__)

#define OS_UNIX

#elif defined(__APPLE__) || defined(__MACH__)

#define OS_APPLE

#endif




#if (defined(OS_WIN32) || defined(OS_WIN64))

typedef void* HANDLE;

#ifndef PLATFORM_HANDLE
#define PLATFORM_HANDLE HANDLE
#endif

#elif ( defined(__unix) || defined(__unix__) )

#ifndef PLATFORM_HANDLE
#define PLATFORM_HANDLE
#endif


#elif ( defined(__APPLE__) || defined(__MACH__) )

#ifndef PLATFORM_HANDLE
#define PLATFORM_HANDLE
#endif

#else
static_assert(false);
#endif




namespace doom
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	namespace os
	{
		//why put _ -> To prevent definition shadowing

		[[nodiscard]] PLATFORM_HANDLE Get_PLATFORM_INVALID_HANDLE_CONSTANT();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>millisecond</returns>
		[[nodiscard]] UINT64 _GetTickCount();
		/// <summary>
		/// sleep for milliseconds
		/// </summary>
		/// <param name="milliseconds">sleep time</param>
		void _Sleep(const UINT32 milliseconds);

		/// <summary>
		/// Processor Number what Current Thread is working on
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] UINT64 _GetCurrentProcessorNumber();
		[[nodiscard]] PLATFORM_HANDLE _GetCurrenThreadHandle();
		[[nodiscard]] UINT64 _GetCurrenThreadID();

		[[nodiscard]] UINT64 _GetThreadStackStartAddress(const PLATFORM_HANDLE threadHandel);


		[[nodiscard]] PLATFORM_HANDLE _GetCurrenProcess();
		[[nodiscard]] bool _SetCurrentProcessAffinityMask(const UINT64 processAffinitMask);
		[[nodiscard]] bool _GetCurrentProcessAffinityMask(
			UINT64& lpProcessAffinityMask, 
			UINT64& lpSystemAffinityMask
		);

		//please set mask of local processor
		//ex) first logical processor -> 1 << 0
		//ex) first logical processor and second -> (1 << 0) | (1 << 1)
		[[nodiscard]] bool _SetThreadAffinity(const PLATFORM_HANDLE threadHandle, const UINT64 threadAffinitMask);
		[[nodiscard]] UINT64 _GetThreadAffinity(const PLATFORM_HANDLE threadHandle);

		
		[[nodiscard]] UINT64 _GetThreadCpuCycle(const PLATFORM_HANDLE threadHandle);
	}
}


