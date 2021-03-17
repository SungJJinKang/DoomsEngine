#include "MainTimer.h"

#include <OS.h>

void doom::time::MainTimer::InitTimer()
{
	unsigned long long currentTickCount = OS::GetSingleton()->_GetTickCount();
	doom::time::MainTimer::mFrameTime.mLastTickCount = currentTickCount;
	doom::time::MainTimer::mFixedTime.mLastTickCount = currentTickCount;
}

void doom::time::MainTimer::UpdateFrameTimer()
{
	unsigned long long currentTime = OS::GetSingleton()->_GetTickCount();
	doom::time::MainTimer::mFrameTime.mCurrentTickCount = currentTime;

	doom::time::MainTimer::mFrameTime.mDeltaTime = static_cast<float>((currentTime - doom::time::MainTimer::mFrameTime.mLastTickCount)) * 0.001f;
	doom::time::MainTimer::mFrameTime.mLastTickCount = currentTime;
	
	MainTimer::CurrentFrame = static_cast<float>(1.0f / doom::time::MainTimer::mFrameTime.mDeltaTime);
	
	++mFrameCounter;
}

void doom::time::MainTimer::ResetFixedTimer()
{
	doom::time::MainTimer::mFixedTime.mLastTickCount = OS::GetSingleton()->_GetTickCount();
}

void doom::time::MainTimer::UpdateFixedTimer()
{
	unsigned long long currentTime = OS::GetSingleton()->_GetTickCount();
	doom::time::MainTimer::mFixedTime.mCurrentTickCount = currentTime;

	doom::time::MainTimer::mFixedTime.mDeltaTime = (currentTime - doom::time::MainTimer::mFixedTime.mLastTickCount) * 0.001f;
	doom::time::MainTimer::mFixedTime.mLastTickCount = currentTime;

	//D_DEBUG_LOG({ "Current Frame : ", std::to_string(1.0 / doom::time::Time_Server::mDeltaTime) });
	//D_DEBUG_LOG({ "Fixed Delta Frame : ", std::to_string(doom::time::MainTimer::mFixedTime.mDeltaTime) });
}

void doom::time::MainTimer::AdvanceAFrame()
{

}
