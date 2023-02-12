#include "RunnableThread.h"

dooms::thread::RunnableThread::RunnableThread()
{
	AddToRootObjectList();
}

void dooms::thread::RunnableThread::InitFromThreadCreater()
{
	D_DEBUG_LOG(eLogType::D_LOG, "Thread ( %s ) is initialized", GetThreadName());

	if(IsCreateNewThread() == true)
	{
		Thread = std::make_unique<std::thread>(&dooms::thread::RunnableThread::Run_RunnableThread, this);
		SetThreadHandle(Thread->native_handle());
	}
	SetThreadPriority(GetRecommendedPriorityOfThreadType());
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
	D_ASSERT(RunnableThread::GetThreadLocalRunnableThreadStackStartAddress() != 0);
	
	UINT8 CurrentStack;

	return (address >= &CurrentStack) && (reinterpret_cast<UINT64>(address) <= RunnableThread::GetThreadLocalRunnableThreadStackStartAddress());
}

HANDLE dooms::thread::RunnableThread::GetPlatformThreadHandler() const
{
	return PlatformThreadHandler;
}

bool dooms::thread::RunnableThread::IsValidPlatformThreadHandler() const
{
	return GetPlatformThreadHandler() != dooms::os::GetPlatformInvalidHandleValue();
}

UINT64 dooms::thread::RunnableThread::GetThreadCPUCycle() const
{
	D_ASSERT(IsValidPlatformThreadHandler() == true);
	return dooms::os::GetThreadCpuCycle(GetPlatformThreadHandler());
}

void dooms::thread::RunnableThread::InitFromRunnableThread()
{
	ThreadLocalRunnableThread = this;
	ThreadLocalRunnableThreadStackStartAddress = dooms::os::GetThreadStackStartAddress(GetThreadHandle());

	bIsInitialized = true;

}

void dooms::thread::RunnableThread::TickFromRunnableThread()
{
}

void dooms::thread::RunnableThread::OnTerminateRunnableThread_OnRunnableThread()
{
	D_DEBUG_LOG(eLogType::D_LOG, "Thread ( %s ) is terminated", GetThreadName());

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

void dooms::thread::RunnableThread::WakeUpRunnableThread()
{
}

void dooms::thread::RunnableThread::OnSetPendingKill()
{
	Base::OnSetPendingKill();

	if(bIsTerminated == false)
	{
		TerminateRunnableThread(true);
	}
	
}

void dooms::thread::RunnableThread::Run_RunnableThread()
{
	if (bIsInitialized == false)
	{
		InitFromRunnableThread();
	}

	while (bIsTerminated == false)
	{
		TickFromRunnableThread();
	}

	OnTerminateRunnableThread_OnRunnableThread();
}

void dooms::thread::RunnableThread::SetThreadPriority(const EThreadPriority ThreadPriority)
{
	INT64 OsDependentThreadPriorityValue = 0;
	const bool bIsSuccess = dooms::os::ConvertThreadPriorityToOsDependentValue(ThreadPriority, OsDependentThreadPriorityValue);
	D_ASSERT(bIsSuccess);
	dooms::os::SetPriorityOfThread(GetThreadHandle(), OsDependentThreadPriorityValue);
}

void dooms::thread::RunnableThread::TerminateRunnableThread(const bool bJoin)
{
	const bool bIsTerminatedOriginal = bIsTerminated;

	bIsTerminated = true;

	if(IsCreateNewThread() && (bIsTerminatedOriginal == false))
	{
		D_ASSERT_LOG(IsExistThreadObject(), "Thread object doesn't exist");
		
		WakeUpRunnableThread();

		if ((Thread != nullptr) && (bJoin == true))
		{
			Thread->join();
		}
	}
}