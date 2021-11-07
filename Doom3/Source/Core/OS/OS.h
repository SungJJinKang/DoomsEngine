#pragma once

#include <Core.h>

#include <string>


using HANDLE = void*;



namespace dooms
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	namespace os
	{
		//why put _ -> To prevent definition shadowing

		NO_DISCARD HANDLE Get_PLATFORM_INVALID_HANDLE_CONSTANT();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>millisecond</returns>
		NO_DISCARD UINT64 _GetTickCount();
		/// <summary>
		/// sleep for milliseconds
		/// </summary>
		/// <param name="milliseconds">sleep time</param>
		void _Sleep(const UINT32 milliseconds);

		/// <summary>
		/// Processor Number what Current Thread is working on
		/// </summary>
		/// <returns></returns>
		NO_DISCARD UINT64 _GetCurrentProcessorNumber();
		NO_DISCARD HANDLE _GetCurrenThreadHandle();
		NO_DISCARD UINT64 _GetCurrenThreadID();

		NO_DISCARD UINT64 _GetThreadStackStartAddress(const HANDLE threadHandel);


		NO_DISCARD HANDLE _GetCurrenProcess();
		NO_DISCARD bool _SetCurrentProcessAffinityMask(const UINT64 processAffinitMask);
		NO_DISCARD bool _GetCurrentProcessAffinityMask(
			UINT64& lpProcessAffinityMask, 
			UINT64& lpSystemAffinityMask
		);

		//please set mask of local processor
		//ex) first logical processor -> 1 << 0
		//ex) first logical processor and second -> (1 << 0) | (1 << 1)
		NO_DISCARD bool _SetThreadAffinity(const HANDLE threadHandle, const UINT64 threadAffinitMask);
		NO_DISCARD UINT64 _GetThreadAffinity(const HANDLE threadHandle);

		
		NO_DISCARD UINT64 _GetThreadCpuCycle(const HANDLE threadHandle);

		NO_DISCARD std::string _GetCurrentExecutableDirectory();
	}
}


