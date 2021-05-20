#include "MainTimer.h"


void doom::time::MainTimer::InitTimer()
{
	double currentTickCount = glfwGetTime();
	doom::time::MainTimer::mFrameTime.mLastTickCount = currentTickCount;
	doom::time::MainTimer::mFixedTime.mLastTickCount = currentTickCount;
}

