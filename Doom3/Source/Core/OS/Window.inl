#include <Windows.h>

unsigned long long doom::OS::_GetTickCount()
{
#if defined(_WIN32)
	return GetTickCount();
#elif defined(_WIN64)
	return GetTickCount64();
#endif
}

void doom::OS::_Sleep(unsigned long milliseconds)
{
	Sleep(milliseconds);
}
