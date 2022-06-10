#include "JobPool.h"

#include "RunnableThread/JobThread.h"
#include "ThreadManager.h"

INT32 dooms::thread::JobPool::GetJobThreadCount() const
{
	return ThreadManager::GetSingleton()->GetRunnableThreadCount(eThreadType::JOB_THREAD);
}

void dooms::thread::JobPool::WakeUpJobThreads()
{
	std::vector<RunnableThread*> JobThreadList = ThreadManager::GetSingleton()->GetRunnableThreadList(eThreadType::JOB_THREAD);
	for(RunnableThread* Thread : JobThreadList)
	{
		CastTo<JobThread*>(Thread)->EnqueueJob([]() {});
	}
}
