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

	EnqueueJob([]() {});
}

void dooms::thread::JobThread::Init_OnRunnableThread()
{
	RunnableThread::Init_OnRunnableThread();
}

void dooms::thread::JobThread::Tick_OnRunnableThread()
{
	RunnableThread::Tick_OnRunnableThread();

	JobPool::JOB_TYPE Job{};

	JobQueue.try_dequeue(Job); // try_dequeue doesn't block thread

	if (static_cast<bool>(Job) == false)
	{
		JobPool::GetSingleton()->TryDequeue(Job);
	}

	if (static_cast<bool>(Job) == false)
	{
		JobQueue.wait_dequeue(Job); // block thread until take element from queue
	}

	if (static_cast<bool>(Job) == true)
	{
		Job();
	}
}
