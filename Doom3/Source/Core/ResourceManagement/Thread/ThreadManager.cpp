#include "ThreadManager.h"

#include "RunnableThread/RunnableThread.h"
#include "ThreadFactory.h"

dooms::thread::RunnableThread* dooms::thread::ThreadManager::CreateNewRunnableThread(const eThreadType TargetThreadType, const char* const BeautifulThreadName)
{
	dooms::thread::RunnableThread* CreatedThread = nullptr;

	if(GetRunnableThread(BeautifulThreadName) == nullptr)
	{
		CreatedThread = ThreadFactory::CreateRunnableThread(TargetThreadType, BeautifulThreadName);
		if(CreatedThread != nullptr)
		{
			RunnableThreadList.push_back(CreatedThread);
		}
	}
	else
	{
		D_ASSERT_LOG(false, "Thread with same name is found");
	}
	
	return CreatedThread;
}

std::vector<dooms::thread::RunnableThread*> dooms::thread::ThreadManager::GetRunnableThread(const eThreadType TargetThreadType)
{
	std::vector<dooms::thread::RunnableThread*> ThreadList{};

	for (RunnableThread* Thread : RunnableThreadList)
	{
		if (Thread->GetThreadType() == TargetThreadType)
		{
			ThreadList.push_back(Thread);
		}
	}

	return ThreadList;
}

std::vector<const dooms::thread::RunnableThread*> dooms::thread::ThreadManager::GetRunnableThread(const eThreadType TargetThreadType) const
{
	std::vector<const dooms::thread::RunnableThread*> ThreadList{};

	for(const RunnableThread* Thread : RunnableThreadList)
	{
		if(Thread->GetThreadType() == TargetThreadType)
		{
			ThreadList.push_back(Thread);
		}
	}

	return ThreadList;
}

dooms::thread::RunnableThread* dooms::thread::ThreadManager::GetRunnableThread(const char* const ThreadName)
{
	return const_cast<dooms::thread::RunnableThread*>(static_cast<const ThreadManager*>(this)->GetRunnableThread(ThreadName));
}

const dooms::thread::RunnableThread* dooms::thread::ThreadManager::GetRunnableThread(const char* const ThreadName) const
{
	const dooms::thread::RunnableThread* TargetRunnableThread = nullptr;

	for (const RunnableThread* Thread : RunnableThreadList)
	{
		if (Thread->GetBeautifulThreadName() == ThreadName)
		{
			TargetRunnableThread = Thread;
			break;
		}
	}

	return TargetRunnableThread;
}
