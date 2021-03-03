#include "JobSystem.h"

#include "../Core.h"
#include "Thread.h"

using namespace doom::resource;

void JobSystem::Init()
{
	this->InitializeThreads();
}

void JobSystem::Update()
{

}

void doom::resource::JobSystem::OnEndOfFrame()
{
}

void JobSystem::WakeUpAllThreads()
{
	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		if (this->mManagedSubThreads[i].GetIsThreadSleeping() == true)
		{
			this->mManagedSubThreads[i].PushBackJob(std::function<void()>()); // push dummy job
		}
	}
}

void JobSystem::InitializeThreads()
{
	this->mMainThreadId = std::this_thread::get_id();

	this->mManagedSubThreads = std::make_unique<ThreadPool[]>(SUB_THREAD_COUNT);
	

	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].SetPriorityWaitingTaskQueue(&(this->mPriorityWaitingTaskQueue));
	}

	this->bmIsInitialized = true;
}

void JobSystem::DestroyThreads()
{
	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].TerminateThreadPool(true);
	}
	this->bmIsInitialized = false;
}

ThreadPool& doom::resource::JobSystem::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}
