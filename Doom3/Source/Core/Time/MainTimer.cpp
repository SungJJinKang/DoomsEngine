#include "MainTimer.h"

#include <Graphics/GraphicsAPI/GraphicsAPI.h>

void dooms::time::MainTimer::InitTimer()
{
	FLOAT64 currentTickCount = graphics::GraphicsAPI::GetTime();
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTickCount;
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTickCount;
}

void dooms::time::MainTimer::UpdateFrameTimer()
{
	const FLOAT64 currentTime = graphics::GraphicsAPI::GetTime();// os::GetSingleton()->_GetTickCount();
	dooms::time::MainTimer::mFrameTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFrameTime.mDeltaTime = static_cast<FLOAT32>(currentTime - dooms::time::MainTimer::mFrameTime.mLastTickCount);
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTime;

	dooms::time::MainTimer::mFrameCounterForStep++;
	MainTimer::CurrentFrame = static_cast<FLOAT32>(1.0f / dooms::time::MainTimer::mFrameTime.mDeltaTime);
	
	
	
}

void dooms::time::MainTimer::ResetFixedTimer()
{
	dooms::time::MainTimer::mFixedTime.mLastTickCount = graphics::GraphicsAPI::GetTime();
}

void dooms::time::MainTimer::UpdateFixedTimer()
{
	FLOAT64 currentTime = graphics::GraphicsAPI::GetTime();
	dooms::time::MainTimer::mFixedTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFixedTime.mDeltaTime = static_cast<FLOAT32>(currentTime - dooms::time::MainTimer::mFixedTime.mLastTickCount);
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTime;
	
}

