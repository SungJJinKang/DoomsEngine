#include "Window.h"

#include <Windows.h>

unsigned long long doom::Window::_GetTickCount()
{
#if defined(WINDOW32)
	return GetTickCount();
#elif defined(WINDOW64)
	return GetTickCount64();
#endif
}

void doom::Window::_Sleep(unsigned long milliseconds)
{
	Sleep(milliseconds);
}
