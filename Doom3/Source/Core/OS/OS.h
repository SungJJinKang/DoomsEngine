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

		NO_DISCARD HANDLE GetPlatformInvalidHandleValue();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>millisecond</returns>
		NO_DISCARD UINT64 GetTickCount();
		/// <summary>
		/// sleep for milliseconds
		/// </summary>
		/// <param name="milliseconds">sleep time</param>
		void Sleep(const UINT32 milliseconds);

		/// <summary>
		/// Processor Number what Current Thread is working on
		/// </summary>
		/// <returns></returns>
		NO_DISCARD UINT64 GetCurrentProcessorNumber();
		NO_DISCARD HANDLE GetCurrentThreadHandle();
		NO_DISCARD UINT64 GetCurrenThreadID();

		NO_DISCARD UINT64 GetThreadStackStartAddress(const HANDLE threadHandel);


		NO_DISCARD HANDLE GetCurrenProcess();
		NO_DISCARD bool SetCurrentProcessAffinityMask(const UINT64 processAffinitMask);
		NO_DISCARD bool GetCurrentProcessAffinityMask(
			UINT64& lpProcessAffinityMask, 
			UINT64& lpSystemAffinityMask
		);

		//please set mask of local processor
		//ex) first logical processor -> 1 << 0
		//ex) first logical processor and second -> (1 << 0) | (1 << 1)
		NO_DISCARD bool SetThreadAffinity(const HANDLE threadHandle, const UINT64 threadAffinitMask);
		NO_DISCARD UINT64 GetThreadAffinity(const HANDLE threadHandle);

		
		NO_DISCARD UINT64 GetThreadCpuCycle(const HANDLE threadHandle);

		NO_DISCARD std::string GetCurrentExecutableDirectory();
		NO_DISCARD std::wstring GetCurrentExecutableDirectoryUnicode();
	}
}


