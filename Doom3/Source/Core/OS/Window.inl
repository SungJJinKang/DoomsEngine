

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

unsigned long long doom::OS::_SetThreadAffinity(const THREAD_HANDLE threadHandle, const unsigned long long threadAffinitMask)
{
	return SetThreadAffinityMask(threadHandle, threadAffinitMask);
}

/*
unsigned long long doom::OS::_GetThreadAffinity(const THREAD_HANDLE threadHandle)
{
	return SetThreadAffinityMask(threadHandle, threadAffinitMask);
}

unsigned int doom::OS::_GetCurrentProcessorNumber()
{
	return GetCurrentProcessorNumber();
}
*/