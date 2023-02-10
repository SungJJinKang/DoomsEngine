#include "OS.h"

#include <ResourceManagement/Thread/EThreadPriority.h>

#if (defined(OS_WIN32) || defined(OS_WIN64))

#include <Windows.h>
#include <winternl.h>

#ifndef PLATFORM_INVALID_HANDLE_CONSTANT
#define PLATFORM_INVALID_HANDLE_CONSTANT INVALID_HANDLE_VALUE 
#endif


HANDLE dooms::os::GetPlatformInvalidHandleValue()
{
	return PLATFORM_INVALID_HANDLE_CONSTANT;
}

UINT64 dooms::os::GetTickCount()
{
#if defined(OS_WIN32)
	return GetTickCount();
#elif defined(OS_WIN64)
	return GetTickCount64();
#endif
}

void dooms::os::SleepFor(const UINT32 milliseconds)
{
	Sleep(milliseconds);
}

UINT64 dooms::os::GetProcessorNumberOfCallerThreadRunningOn()
{
	return static_cast<UINT64>(GetCurrentProcessorNumber());
}

HANDLE dooms::os::GetCallerThreadHandle()
{
	return GetCurrentThread();
}

UINT64 dooms::os::GetCallerThreadID()
{
	return static_cast<UINT64>(GetCurrentThreadId());
}

#define ThreadQuerySetWin32StartAddress 9
UINT64 dooms::os::GetThreadStackStartAddress(const HANDLE threadHandel)
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

HANDLE dooms::os::GetCurrenProc()
{
	return GetCurrentProcess();
}

bool dooms::os::SetCurrentProcAffinityMask(const UINT64 processAffinitMask)
{
	bool isSuccess = SetProcessAffinityMask(GetCurrentProcess(), static_cast<DWORD_PTR>(processAffinitMask));
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool dooms::os::GetCurrentProcAffinityMask
(
	UINT64& lpProcessAffinityMask,
	UINT64& lpSystemAffinityMask
)
{
	bool isSuccess = GetProcessAffinityMask(GetCurrentProcess(), reinterpret_cast<PDWORD_PTR>(&lpProcessAffinityMask), reinterpret_cast<PDWORD_PTR>(&lpSystemAffinityMask));
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool dooms::os::SetPriorityOfThread(const HANDLE ThreadHandle, const INT64 ThreadPrioirty)
{
	const bool bIsSuccess = SetThreadPriority(ThreadHandle, ThreadPrioirty);
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(bIsSuccess == true);
	return bIsSuccess;
}

bool dooms::os::ConvertThreadPriorityToOsDependentValue(const thread::EThreadPriority ThreadPrioirty, INT64& OutOsDependentThreadPriorityValue)
{
	bool bIsSuccess = true;

	switch(ThreadPrioirty)
	{
		case thread::EThreadPriority::High:
		{
			OutOsDependentThreadPriorityValue = THREAD_PRIORITY_HIGHEST;
			break;
		}
		case thread::EThreadPriority::Middle:
		{
			OutOsDependentThreadPriorityValue = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		}
		case thread::EThreadPriority::Low:
		{
			OutOsDependentThreadPriorityValue = THREAD_PRIORITY_NORMAL;
			break;
		}
		case thread::EThreadPriority::Background:
		{
			// THREAD_MODE_BACKGROUND_BEGIN, THREAD_MODE_BACKGROUND_END?
			OutOsDependentThreadPriorityValue = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		}
		default:
		{
			bIsSuccess = false;
			break;
		}
	}

	return bIsSuccess;
}

bool dooms::os::SetThreadAffinity(const HANDLE threadHandle, const UINT64 threadAffinitMask)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);
	
	SetThreadAffinityMask(threadHandle, *reinterpret_cast<const DWORD_PTR*>(&threadAffinitMask));

	const bool isSuccess = (GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);
	return isSuccess;
}


UINT64 dooms::os::GetThreadAffinity(const HANDLE threadHandle)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);

	//https://stackoverflow.com/questions/6601862/query-thread-not-process-processor-affinity
	const UINT64 originalMask = SetThreadAffinityMask(threadHandle, 0xFFFFFFFFFFFFFFFF);
	//D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	SetThreadAffinityMask(threadHandle, originalMask);
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	return originalMask;
}

UINT64 dooms::os::GetThreadCpuCycle(const HANDLE threadHandle)
{
	UINT64 cycle;
	QueryThreadCycleTime(threadHandle, &cycle);
	return cycle;
}

std::string dooms::os::GetCurrentExecutableDirectory()
{
	static std::string currentExePath{};

	if(currentExePath.empty() == true)
	{

#ifdef UNICODE

		WCHAR unicodeBuffer[256];
		DWORD stringCount = GetModuleFileNameW(NULL, unicodeBuffer, 256);
		D_ASSERT(GetLastError() != ERROR_INSUFFICIENT_BUFFER); // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew


		char strUtf8[256];
		int utf8Length = WideCharToMultiByte(CP_UTF8, 0, unicodeBuffer, stringCount, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, unicodeBuffer, stringCount, strUtf8, utf8Length, NULL, NULL);
		currentExePath = strUtf8;

#else

		CHAR utf8Buffer[256];
		DWORD stringCount = GetModuleFileNameA(NULL, utf8Buffer, 256);
		D_ASSERT(GetLastError() != ERROR_INSUFFICIENT_BUFFER); // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew
		currentExePath = utf8Buffer;

#endif

		const std::string::size_type lastBackSlashPos = currentExePath.find_last_of('\\');
		currentExePath = currentExePath.substr(0, lastBackSlashPos);
	}

	

	return currentExePath;
}

std::wstring dooms::os::GetCurrentExecutableDirectoryUnicode()
{
	static std::wstring currentExePath{};

	if (currentExePath.empty() == true)
	{
		WCHAR unicodeBuffer[256];
		DWORD stringCount = GetModuleFileNameW(NULL, unicodeBuffer, 256);
		D_ASSERT(GetLastError() != ERROR_INSUFFICIENT_BUFFER); // https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew

		currentExePath = unicodeBuffer;
		const std::wstring::size_type lastBackSlashPos = currentExePath.find_last_of(L'\\');
		currentExePath = currentExePath.substr(0, lastBackSlashPos);
	}
	
	return currentExePath;
}


#endif