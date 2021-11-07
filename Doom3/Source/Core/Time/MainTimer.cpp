#include "MainTimer.h"

void dooms::time::MainTimer::InitTimer()
{
	FLOAT64 currentTickCount = glfwGetTime();
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTickCount;
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTickCount;
}

void dooms::time::MainTimer::UpdateFrameTimer()
{
	const FLOAT64 currentTime = glfwGetTime();// os::GetSingleton()->_GetTickCount();
	dooms::time::MainTimer::mFrameTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFrameTime.mDeltaTime = static_cast<FLOAT32>(currentTime - dooms::time::MainTimer::mFrameTime.mLastTickCount);
	dooms::time::MainTimer::mFrameTime.mLastTickCount = currentTime;

	dooms::time::MainTimer::mFrameCounterForStep++;
	MainTimer::CurrentFrame = static_cast<FLOAT32>(1.0f / dooms::time::MainTimer::mFrameTime.mDeltaTime);
	
	
	
}

void dooms::time::MainTimer::ResetFixedTimer()
{
	dooms::time::MainTimer::mFixedTime.mLastTickCount = glfwGetTime();
}

void dooms::time::MainTimer::UpdateFixedTimer()
{
	FLOAT64 currentTime = glfwGetTime();
	dooms::time::MainTimer::mFixedTime.mCurrentTickCount = currentTime;

	dooms::time::MainTimer::mFixedTime.mDeltaTime = static_cast<FLOAT32>(currentTime - dooms::time::MainTimer::mFixedTime.mLastTickCount);
	dooms::time::MainTimer::mFixedTime.mLastTickCount = currentTime;

#ifdef DEBUG_MODE
	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F5))
	{
		D_DEBUG_LOG({ "Current Frame : ", std::to_string(1.0 / dooms::time::MainTimer::mFrameTime.mDeltaTime) });
	}
#endif
}

