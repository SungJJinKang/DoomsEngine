#include "OS.h"


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

void dooms::os::Sleep(const UINT32 milliseconds)
{
	Sleep(milliseconds);
}

UINT64 dooms::os::GetCurrentProcessorNumber()
{
	return static_cast<UINT64>(GetCurrentProcessorNumber());
}

HANDLE dooms::os::GetCurrentThreadHandle()
{
	return GetCurrentThread();
}

UINT64 dooms::os::GetCurrenThreadID()
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

HANDLE dooms::os::GetCurrenProcess()
{
	return GetCurrentProcess();
}

bool dooms::os::SetCurrentProcessAffinityMask(const UINT64 processAffinitMask)
{
	bool isSuccess = SetProcessAffinityMask(GetCurrentProcess(), static_cast<DWORD_PTR>(processAffinitMask));
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool dooms::os::GetCurrentProcessAffinityMask
(
	UINT64& lpProcessAffinityMask,
	UINT64& lpSystemAffinityMask
)
{
	bool isSuccess = GetProcessAffinityMask(GetCurrentProcess(), reinterpret_cast<PDWORD_PTR>(&lpProcessAffinityMask), reinterpret_cast<PDWORD_PTR>(&lpSystemAffinityMask));
	D_ASSERT(isSuccess == true);

	return isSuccess;
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

/*
UINT32 dooms::os::GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}
*/





#endif