#include "MainTimer.h"

#include "TickCount.h"

void doom::time::MainTimer::InitTimer()
{
	doom::time::MainTimer::mLastTickCount = TickCount::GetTickCount();
}

void doom::time::MainTimer::UpdateTimer()
{
	unsigned long long currentTime = TickCount::GetTickCount();
	doom::time::MainTimer::mCurrentTickCount = currentTime;

	doom::time::MainTimer::mDeltaTime = (currentTime - doom::time::MainTimer::mLastTickCount) * 0.001f;
	doom::time::MainTimer::mLastTickCount = currentTime;

	//D_DEBUG_LOG({ "Current Frame : ", std::to_string(1.0 / doom::time::Time_Server::mDeltaTime) });
	//D_DEBUG_LOG({ "Delta Frame : ", std::to_string(mDeltaTime) });
	++mFrameCounter;
}
