#include "MainTimer.h"

#include "TickCount.h"

void doom::time::MainTimer::InitTimer()
{
	doom::time::MainTimer::mLastTickCount = TickCount::GetTickCount();
}

void doom::time::MainTimer::UpdateTimer()
{
	auto currentTime = TickCount::GetTickCount();
	doom::time::MainTimer::mCurrentTickCount = currentTime;

	doom::time::MainTimer::mDeltaTime = (currentTime - doom::time::MainTimer::mLastTickCount) * 0.000001f;
	doom::time::MainTimer::mLastTickCount = currentTime;

	//D_DEBUG_LOG({ "Current Frame : ", std::to_string(1.0 / doom::time::Time_Server::mDeltaTime) });
	++mFrameCounter;
}
