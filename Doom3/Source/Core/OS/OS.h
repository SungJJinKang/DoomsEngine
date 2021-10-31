#pragma once

#include <Core.h>



using HANDLE = void*;



namespace doom
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	namespace os
	{
		//why put _ -> To prevent definition shadowing

		[[nodiscard]] HANDLE Get_PLATFORM_INVALID_HANDLE_CONSTANT();

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
		[[nodiscard]] HANDLE _GetCurrenThreadHandle();
		[[nodiscard]] UINT64 _GetCurrenThreadID();

		[[nodiscard]] UINT64 _GetThreadStackStartAddress(const HANDLE threadHandel);


		[[nodiscard]] HANDLE _GetCurrenProcess();
		[[nodiscard]] bool _SetCurrentProcessAffinityMask(const UINT64 processAffinitMask);
		[[nodiscard]] bool _GetCurrentProcessAffinityMask(
			UINT64& lpProcessAffinityMask, 
			UINT64& lpSystemAffinityMask
		);

		//please set mask of local processor
		//ex) first logical processor -> 1 << 0
		//ex) first logical processor and second -> (1 << 0) | (1 << 1)
		[[nodiscard]] bool _SetThreadAffinity(const HANDLE threadHandle, const UINT64 threadAffinitMask);
		[[nodiscard]] UINT64 _GetThreadAffinity(const HANDLE threadHandle);

		
		[[nodiscard]] UINT64 _GetThreadCpuCycle(const HANDLE threadHandle);
	}
}


