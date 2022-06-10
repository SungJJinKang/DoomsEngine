#include "RunnableThread.h"

dooms::thread::RunnableThread::RunnableThread()
{
}

void dooms::thread::RunnableThread::Init_OnCallerThread()
{
	D_DEBUG_LOG(eLogType::D_LOG, "Thread ( %s ) is initialized", BeautifulRunnableThreadName.c_str());

	if(IsCreateNewThread() == true)
	{
		Thread = std::make_unique<std::thread>(&dooms::thread::RunnableThread::Run_RunnableThread, this);
		SetThreadHandle(Thread->native_handle());
	}
}

bool dooms::thread::RunnableThread::IsInitialized() const
{
	return bIsInitialized;
}

bool dooms::thread::RunnableThread::IsTerminated() const
{
	return bIsTerminated;
}

dooms::thread::RunnableThread* dooms::thread::RunnableThread::GetThreadLocalRunnableThread()
{
	return ThreadLocalRunnableThread;
}

UINT64 dooms::thread::RunnableThread::GetThreadLocalRunnableThreadStackStartAddress()
{
	return ThreadLocalRunnableThreadStackStartAddress;
}

bool dooms::thread::RunnableThread::IsOnThreadStack(const void* const address)
{
	assert(RunnableThread::GetThreadLocalRunnableThreadStackStartAddress() != nullptr);
	
	UINT8 CurrentStack;

	return (address >= &CurrentStack) && (reinterpret_cast<UINT64>(address) <= RunnableThread::GetThreadLocalRunnableThreadStackStartAddress());
}

HANDLE dooms::thread::RunnableThread::GetPlatformThreadHandler() const
{
	return PlatformThreadHandler;
}

bool dooms::thread::RunnableThread::IsValidPlatformThreadHandler()
{
	return GetPlatformThreadHandler() != dooms::os::Get_PLATFORM_INVALID_HANDLE_CONSTANT();
}

void dooms::thread::RunnableThread::Init_OnRunnableThread()
{
	ThreadLocalRunnableThread = this;
	ThreadLocalRunnableThreadStackStartAddress = dooms::os::_GetThreadStackStartAddress(GetThreadHandle());

	bIsInitialized = true;

}

void dooms::thread::RunnableThread::Tick_OnRunnableThread()
{
}

void dooms::thread::RunnableThread::OnTerminateRunnableThread_OnRunnableThread()
{
	D_DEBUG_LOG("Thread ( %s ) is terminated", GetThreadName());

}

bool dooms::thread::RunnableThread::IsCreateNewThread()
{
	return true;
}

void dooms::thread::RunnableThread::SetThreadHandle(HANDLE Handle)
{
	PlatformThreadHandler = Handle;
}

HANDLE dooms::thread::RunnableThread::GetThreadHandle()
{
	return PlatformThreadHandler;
}

bool dooms::thread::RunnableThread::IsExistThreadObject() const
{
	return (Thread != nullptr);
}

void dooms::thread::RunnableThread::Run_RunnableThread()
{
	if (bIsInitialized == false)
	{
		Init_OnRunnableThread();
	}

	while (bIsTerminated == false)
	{
		Tick_OnRunnableThread();
	}

	OnTerminateRunnableThread_OnRunnableThread();
}

bool dooms::thread::IsInGameThread()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return (dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType() == eThreadType::GAME_THREAD);
}

bool dooms::thread::IsInRenderThread()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return (dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType() == eThreadType::RENDER_THREAD);
}

dooms::thread::eThreadType dooms::thread::GetLocalThreadType()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType();
}

void dooms::thread::RunnableThread::TerminateRunnableThread(const bool bJoin)
{
	D_ASSERT(bInitialized == true);
	D_ASSERT_LOG(IsExistThreadObject(), "Thread object doesn't exist");

	bIsTerminated = true;

	if ((bJoin == true) && (Thread != nullptr))
	{
		Thread->join();
	}
}