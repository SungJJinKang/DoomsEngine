

unsigned long long doom::OS::_GetTickCount()
{
#if defined(_WIN32)
	return GetTickCount();
#elif defined(_WIN64)
	return GetTickCount64();
#endif
}

void doom::OS::_Sleep(const unsigned long milliseconds)
{
	Sleep(milliseconds);
}

unsigned int doom::OS::_GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}

THREAD_HANDLE doom::OS::_GetCurrenThreadHandle()
{
	return GetCurrentThread();
}

unsigned int doom::OS::_GetCurrenThreadID()
{
	return GetCurrentThreadId();
}

void doom::OS::_SetThreadAffinity(const THREAD_HANDLE threadHandle, const unsigned long long threadAffinitMask)
{
	SetThreadAffinityMask(threadHandle, threadAffinitMask);
}


unsigned long long doom::OS::_GetCurrentThreadAffinity(const THREAD_HANDLE threadHandle)
{
	//https://stackoverflow.com/questions/6601862/query-thread-not-process-processor-affinity
	const unsigned long long originalMask = SetThreadAffinityMask(threadHandle, 0xFFFFFFFFFFFFFFFF);
	SetThreadAffinityMask(threadHandle, originalMask);
	return originalMask;
}

/*
unsigned int doom::OS::_GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}
*/