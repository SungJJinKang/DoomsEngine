#include "JobThread.h"

dooms::thread::JobThread::JobThread()
{
}

dooms::thread::eThreadType dooms::thread::JobThread::GetThreadType() const
{
	return dooms::thread::eThreadType::JOB_THREAD;
}

const char* dooms::thread::JobThread::GetThreadName() const
{
	return "JobThread";
}

void dooms::thread::JobThread::SetJobPool(thread::JobPool* InJobPool)
{
	JobPool = InJobPool;
}

bool dooms::thread::JobThread::IsAllowMultipleThreadOfThisThreadType() const
{
	return true;
}

void dooms::thread::JobThread::WakeUpRunnableThread()
{
	Base::WakeUpRunnableThread();

	//EnqueueJob([]() {});
}

void dooms::thread::JobThread::Init_OnRunnableThread()
{
	RunnableThread::Init_OnRunnableThread();
}

void dooms::thread::JobThread::Tick_OnRunnableThread()
{
	RunnableThread::Tick_OnRunnableThread();

	JobPool::JOB_TYPE Job{};

	while (true)
	{
		bool IsCurrentThreadJobQueueHasItem = JobQueue.try_dequeue(Job);
		if (IsCurrentThreadJobQueueHasItem == false)
		{
			const bool IsGlobalThreadJobQueueHasItem = JobPool::GetSingleton()->TryDequeue(Job);
			if (IsGlobalThreadJobQueueHasItem == true)
			{
				// check again if current thread job queue has a item
				IsCurrentThreadJobQueueHasItem = JobQueue.try_dequeue(Job);
				break;
			}
		}
		else
		{
			break;
		}

		if (IsTerminated())
		{
			break;
		}

		std::this_thread::yield();
	}
	

	if (static_cast<bool>(Job) == true)
	{
		Job();
	}
}
