


unsigned long long doom::os::_GetTickCount()
{
#if defined(OS_WIN32)
	return GetTickCount();
#elif defined(OS_WIN64)
	return GetTickCount64();
#endif
}

void doom::os::_Sleep(const unsigned long milliseconds)
{
	Sleep(milliseconds);
}

unsigned long long doom::os::_GetCurrentProcessorNumber()
{
	return static_cast<unsigned long long>(GetCurrentProcessorNumber());
}

PLATFORM_HANDLE doom::os::_GetCurrenThreadHandle()
{
	return GetCurrentThread();
}

unsigned long long doom::os::_GetCurrenThreadID()
{
	return static_cast<unsigned long long>(GetCurrentThreadId());
}

#define ThreadQuerySetWin32StartAddress 9
unsigned long long doom::os::_GetThreadStackStartAddress(const PLATFORM_HANDLE threadHandel)
{
	NTSTATUS ntStatus;
	DWORD_PTR dwStartAddress;


	ntStatus = NtQueryInformationThread(threadHandel, (THREADINFOCLASS)ThreadQuerySetWin32StartAddress, (PVOID)(&dwStartAddress), sizeof(DWORD_PTR), NULL);
	
	D_ASSERT(ntStatus == 0x00000000);

	if (ntStatus == 0x00000000)
	{
		return static_cast<unsigned long long>(dwStartAddress);
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

bool doom::os::_SetCurrentProcessAffinityMask(const unsigned long long processAffinitMask)
{
	bool isSuccess = SetProcessAffinityMask(GetCurrentProcess(), static_cast<DWORD_PTR>(processAffinitMask));
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool doom::os::_GetCurrentProcessAffinityMask
(
	unsigned long long& lpProcessAffinityMask,
	unsigned long long& lpSystemAffinityMask
)
{
	bool isSuccess = GetProcessAffinityMask(GetCurrentProcess(), &lpProcessAffinityMask, &lpSystemAffinityMask);
	D_ASSERT(isSuccess == true);

	return isSuccess;
}

bool doom::os::_SetThreadAffinity(const PLATFORM_HANDLE threadHandle, const unsigned long long threadAffinitMask)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);
	
	SetThreadAffinityMask(threadHandle, *reinterpret_cast<const DWORD_PTR*>(&threadAffinitMask));

	const bool isSuccess = (GetLastError() != ERROR_INVALID_PARAMETER);
	D_ASSERT(isSuccess == true);
	return isSuccess;
}


unsigned long long doom::os::_GetThreadAffinity(const PLATFORM_HANDLE threadHandle)
{
	D_ASSERT(threadHandle != PLATFORM_INVALID_HANDLE_CONSTANT);

	//https://stackoverflow.com/questions/6601862/query-thread-not-process-processor-affinity
	const unsigned long long originalMask = SetThreadAffinityMask(threadHandle, 0xFFFFFFFFFFFFFFFF);
	//D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	SetThreadAffinityMask(threadHandle, originalMask);
	D_ASSERT(GetLastError() != ERROR_INVALID_PARAMETER);

	return originalMask;
}

unsigned long long doom::os::_GetThreadCpuCycle(const PLATFORM_HANDLE threadHandle)
{
	unsigned long long cycle;
	QueryThreadCycleTime(threadHandle, &cycle);
	return cycle;
}

/*
unsigned int doom::os::_GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}
*/