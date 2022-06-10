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

	SetThreadHandle(dooms::os::_GetCurrenThreadHandle());
	Init_OnRunnableThread();
	// This function should be called by main thread
}

bool dooms::thread::GameThread::IsAllowMultipleThreadOfThisThreadType() const
{
	return false;
}

bool dooms::thread::GameThread::IsCreateNewThread()
{
	return false;
}
