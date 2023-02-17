#include "JobPool.h"

#include "RunnableThread/JobThread.h"
#include "ThreadManager.h"

bool dooms::thread::JobPool::TryDequeue(JOB_TYPE& Job)
{
	return GlobalJobQueue.try_dequeue(Job);
}

INT32 dooms::thread::JobPool::GetJobThreadCount() const
{
	return ThreadManager::GetSingleton()->GetRunnableThreadCount(EThreadType::JOB_THREAD);
}

void dooms::thread::JobPool::WakeUpJobThreads()
{
	std::vector<RunnableThread*> JobThreadList = ThreadManager::GetSingleton()->GetRunnableThreadList(EThreadType::JOB_THREAD);
	for(RunnableThread* Thread : JobThreadList)
	{
		Thread->WakeUpRunnableThread();
	}
}
