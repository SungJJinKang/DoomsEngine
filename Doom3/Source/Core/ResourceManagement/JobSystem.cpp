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
	for (auto& thread : this->mManagedSubThreads)
	{
		if (thread.GetIsThreadSleeping() == true)
		{
			thread.PushBackJob(std::function<void()>()); // push dummy job
		}
	}
}

void JobSystem::InitializeThreads()
{
	this->mMainThreadId = std::this_thread::get_id();

	for (auto& thread : this->mManagedSubThreads)
	{
		thread.SetPriorityWaitingTaskQueue(&(this->mPriorityWaitingTaskQueue));
	}

	this->bmIsInitialized = true;
}

void JobSystem::DestroyThreads()
{
	for (auto& thread : this->mManagedSubThreads)
	{
		thread.TerminateThreadPool(true);
	}
	this->bmIsInitialized = false;
}

ThreadPool& doom::resource::JobSystem::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}
