#include "GameThread.h"

#include <thread>

const char* dooms::thread::GameThread::GetThreadName() const
{
	return "Game Thread";
}

dooms::thread::EThreadType dooms::thread::GameThread::GetThreadType() const
{
	return EThreadType::GAME_THREAD;
}

void dooms::thread::GameThread::InitFromCallerThread()
{
	SetThreadHandle(dooms::os::GetCallerThreadHandle());

	Base::InitFromCallerThread();
	
	InitFromRunnableThread();
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

void dooms::thread::GameThread::TickFromRunnableThread()
{
	Base::TickFromRunnableThread();

	const bool bIsStillRun = TickFunction();

	if(bIsStillRun == false)
	{
		TerminateRunnableThread(false);
	}
}

dooms::thread::EThreadPriority dooms::thread::GameThread::GetRecommendedPriorityOfThreadType() const
{
	return dooms::thread::EThreadPriority::High;
}
