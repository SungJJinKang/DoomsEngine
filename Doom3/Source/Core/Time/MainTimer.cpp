#include "MainTimer.h"

#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include <Windows.h>

static double PCFreq = 0.0;
static __int64 CounterStart = 0;

void dooms::time::MainTimer::InitTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
	{
		D_ASSERT(false);
	}

	PCFreq = double(li.QuadPart);

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;

	FLOAT64 currentTickCount = GetTime();
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTickCount;
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTickCount;

	
}

FLOAT64 MainTimer::GetTime() const
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void dooms::time::MainTimer::UpdateFrameTimer()
{
	const FLOAT64 currentTime = GetTime();// os::GetSingleton()->_GetTickCount();
	dooms::time::MainTimer::mFrameTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFrameTime.mDeltaTime = static_cast<FLOAT64>(currentTime - dooms::time::MainTimer::mFrameTime.mLastTickCount);
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTime;

	dooms::time::MainTimer::mFrameCounterForStep++;
	MainTimer::CurrentFrame = static_cast<FLOAT64>(1.0 / dooms::time::MainTimer::mFrameTime.mDeltaTime);
	
	
	
}

void dooms::time::MainTimer::ResetFixedTimer()
{
	dooms::time::MainTimer::mFixedTime.mLastTickCount = GetTime();
}

void dooms::time::MainTimer::UpdateFixedTimer()
{
	FLOAT64 currentTime = GetTime();
	dooms::time::MainTimer::mFixedTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFixedTime.mDeltaTime = static_cast<FLOAT64>(currentTime - dooms::time::MainTimer::mFixedTime.mLastTickCount);
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTime;
	
}

