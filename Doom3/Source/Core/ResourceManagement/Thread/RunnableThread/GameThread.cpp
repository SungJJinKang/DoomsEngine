#include "GameThread.h"

#include <thread>

const char* dooms::thread::GameThread::GetThreadName() const
{
	return "Game Thread";
}

dooms::thread::eThreadType dooms::thread::GameThread::GetThreadType() const
{
	return eThreadType::GAME_THREAD;
}

void dooms::thread::GameThread::Init_OnCallerThread()
{
	RunnableThread::Init_OnCallerThread();

	SetThreadHandle(dooms::os::_GetCurrentThreadHandle());
	Init_OnRunnableThread();
	// This function should be called by main thread
}

bool dooms::thread::GameThread::IsAllowMultipleThreadOfThisThreadType() const
{
	return false;
}

void dooms::thread::GameThread::SetTickFunction(std::function<bool()> InTickFunction)
{
	TickFunction = InTickFunction;
}

bool dooms::thread::GameThread::IsCreateNewThread()
{
	return false;
}

void dooms::thread::GameThread::Tick_OnRunnableThread()
{
	RunnableThread::Tick_OnRunnableThread();

	const bool bIsStillRun = TickFunction();

	if(bIsStillRun == false)
	{
		TerminateRunnableThread(false);
	}
}
