#include "OS.h"


#if (defined(OS_WIN32) || defined(OS_WIN64))




#include <Windows.h>
#include <winternl.h>

#ifndef PLATFORM_INVALID_HANDLE_CONSTANT
#define PLATFORM_INVALID_HANDLE_CONSTANT INVALID_HANDLE_VALUE 
#endif


HANDLE doom::os::Get_PLATFORM_INVALID_HANDLE_CONSTANT()
{
	return PLATFORM_INVALID_HANDLE_CONSTANT;
}

UINT64 doom::os::_GetTickCount()
{
#if defined(OS_WIN32)
	return GetTickCount();
#elif defined(OS_WIN64)
	return GetTickCount64();
#endif
}

void doom::os::_Sleep(const UINT32 milliseconds)
{
	Sleep(milliseconds);
}

UINT64 doom::os::_GetCurrentProcessorNumber()
{
	return static_cast<UINT64>(GetCurrentProcessorNumber());
}

HANDLE doom::os::_GetCurrenThreadHandle()
{
	return GetCurrentThread();
}

UINT64 doom::os::_GetCurrenThreadID()
{
	return static_cast<UINT64>(GetCurrentThreadId());
}

#define ThreadQuerySetWin32StartAddress 9
UINT64 doom::os::_GetThreadStackStartAddress(const HANDLE threadHandel)
{
	NTSTATUS ntStatus;
	DWORD_PTR dwStartAddress;


	ntStatus = NtQueryInformationThread(threadHandel, (THREADINFOCLASS)ThreadQuerySetWin32StartAddress, (PVOID)(&dwStartAddress), sizeof(DWORD_PTR), NULL);
	
	D_ASSERT(ntStatus == 0x00000000);

	if (ntStatus == 0x00000000)
	{
		return static_cast<UINT64>(dwStartAddress);
	}
	else
	{
		return 0;
	}
}

HANDLE doom::os::_GetCurrenProcess()
{
	return GetCurrentProcess();
}

bool doom::os::_SetCurrentProcessAffinityMask(const UINT64 processAffinitMask)
{
	bool isSuccess = SetProcessAffinityMask(GetCurrentProcess(), static_cast<DWORD_PTR>(processAffinitMask));
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool doom::os::_GetCurrentProcessAffinityMask
(
	UINT64& lpProcessAffinityMask,
	UINT64& lpSystemAffinityMask
)
{
	bool isSuccess = GetProcessAffinityMask(GetCurrentProcess(), reinterpret_cast<PDWORD_PTR>(&lpProcessAffinityMask), reinterpret_cast<PDWORD_PTR>(&lpSystemAffinityMask));
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool doom::os::_SetThreadAffinity(const HANDLE threadHandle, const UINT64 threadAffinitMask)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);
	
	SetThreadAffinityMask(threadHandle, *reinterpret_cast<const DWORD_PTR*>(&threadAffinitMask));

	const bool isSuccess = (GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);
	return isSuccess;
}


UINT64 doom::os::_GetThreadAffinity(const HANDLE threadHandle)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);

	//https://stackoverflow.com/questions/6601862/query-thread-not-process-processor-affinity
	const UINT64 originalMask = SetThreadAffinityMask(threadHandle, 0xFFFFFFFFFFFFFFFF);
	//D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	SetThreadAffinityMask(threadHandle, originalMask);
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	return originalMask;
}

UINT64 doom::os::_GetThreadCpuCycle(const HANDLE threadHandle)
{
	UINT64 cycle;
	QueryThreadCycleTime(threadHandle, &cycle);
	return cycle;
}

/*
UINT32 doom::os::_GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}
*/





#endif