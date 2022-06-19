#include "ThreadManager.h"

#include "RunnableThread/RunnableThread.h"
#include "ThreadFactory.h"

void dooms::thread::ThreadManager::Init(const int argc, char* const* const argv)
{
}

void dooms::thread::ThreadManager::Update()
{
}

void dooms::thread::ThreadManager::OnEndOfFrame()
{
}

dooms::thread::RunnableThread* dooms::thread::ThreadManager::CreateNewRunnableThread(const eThreadType TargetThreadType)
{
	std::scoped_lock<std::recursive_mutex> Lock{ RunnableThreadListMutex };

	dooms::thread::RunnableThread* CreatedThread = ThreadFactory::CreateRunnableThread(TargetThreadType);

	if((CreatedThread->IsAllowMultipleThreadOfThisThreadType() == true) || (GetRunnableThreadCount(TargetThreadType) == 0))
	{
		RunnableThreadList.push_back(CreatedThread);

		CreatedThread->Init_OnCallerThread();
	}
	else
	{
		D_ASSERT_LOG(false, "This type ( %s ) thread is not allowed to be created multiple times", CreatedThread->GetThreadName());

		CreatedThread->SetIsPendingKill();

		CreatedThread = nullptr;
	}

	return CreatedThread;
}

std::vector<dooms::thread::RunnableThread*> dooms::thread::ThreadManager::CreateNewRunnableThread(const eThreadType TargetThreadType, const INT32 Count)
{
	std::vector<dooms::thread::RunnableThread*> CreatedThreadList{};

	for(INT32 Index = 0 ; Index < Count ; Index++)
	{
		CreatedThreadList.push_back(CreateNewRunnableThread(TargetThreadType));
	}

	return CreatedThreadList;
}

void dooms::thread::ThreadManager::TerminateRunnableThread(const eThreadType TargetThreadType, const INT32 Index, const bool bJoin)
{
	std::scoped_lock<std::recursive_mutex> Lock{ RunnableThreadListMutex };

	bool bIsTerminated = false;

	INT32 ThreadCounter = 0;

	for(INT32 ThreadIndex = 0 ; ThreadIndex < RunnableThreadList.size() ; ThreadIndex++)
	{
		if(RunnableThreadList[ThreadIndex]->GetThreadType() == TargetThreadType)
		{
			if(ThreadCounter == Index)
			{
				RunnableThreadList[ThreadIndex]->TerminateRunnableThread(bJoin);
				RunnableThreadList.erase(RunnableThreadList.begin() + ThreadIndex);

				bIsTerminated = true;

				break;
			}

			ThreadCounter++;
		}
	}

	D_ASSERT(bIsTerminated == true);
}

void dooms::thread::ThreadManager::TerminateAllRunnableThread(const bool bJoin)
{
	std::scoped_lock<std::recursive_mutex> Lock{ RunnableThreadListMutex };
	
	for (INT32 ThreadIndex = 0; ThreadIndex < RunnableThreadList.size(); ThreadIndex++)
	{
		RunnableThreadList[ThreadIndex]->TerminateRunnableThread(bJoin);
		RunnableThreadList.erase(RunnableThreadList.begin() + ThreadIndex);

		ThreadIndex--;
	}
}

std::vector<dooms::thread::RunnableThread*> dooms::thread::ThreadManager::GetRunnableThreadList() const
{
	return RunnableThreadList;
}

std::vector<dooms::thread::RunnableThread*> dooms::thread::ThreadManager::GetRunnableThreadList(const eThreadType TargetThreadType) const
{
	std::scoped_lock<std::recursive_mutex> Lock{ RunnableThreadListMutex };

	std::vector<dooms::thread::RunnableThread*> TargetRunnableThreadList{};

	for (RunnableThread* Thread : RunnableThreadList)
	{
		if (Thread->GetThreadType() == TargetThreadType)
		{
			TargetRunnableThreadList.push_back(Thread);
		}
	}

	return TargetRunnableThreadList;
}

INT64 dooms::thread::ThreadManager::GetRunnableThreadCount() const
{
	return RunnableThreadList.size();
}

INT64 dooms::thread::ThreadManager::GetRunnableThreadCount(const eThreadType TargetThreadType) const
{
	std::scoped_lock<std::recursive_mutex> Lock{ RunnableThreadListMutex };

	INT64 RunnableThreadCount = 0;

	for (RunnableThread* Thread : RunnableThreadList)
	{
		if (Thread->GetThreadType() == TargetThreadType)
		{
			RunnableThreadCount++;
		}
	}

	return RunnableThreadCount;
}

INT64 dooms::thread::ThreadManager::GetTotalRunnableThreadCount() const
{
	return RunnableThreadList.size();
}

INT32 dooms::thread::ThreadManager::GetCallerThreadIndexOfSameTypeThreads() const
{
	const RunnableThread* const CallerThread = RunnableThread::GetThreadLocalRunnableThread();
	const eThreadType CallerThreadType = CallerThread->GetThreadType();

	INT32 Index = 0;

	for(RunnableThread* Thread : RunnableThreadList)
	{
		if(Thread->GetThreadType() == CallerThreadType)
		{
			if(CallerThread == Thread)
			{
				break;
			}

			Index++;
		}
	}

	return Index;
}

void dooms::thread::ThreadManager::OnSetPendingKill()
{
	Base::OnSetPendingKill();

	TerminateAllRunnableThread(true);
}
