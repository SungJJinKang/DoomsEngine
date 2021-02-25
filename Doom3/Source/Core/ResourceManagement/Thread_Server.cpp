#include "Thread_Server.h"

#include "../Core.h"
#include "Thread.h"

using namespace doom::resource;

void Thread_Server::Init()
{
	this->InitializeThreads();
}

void Thread_Server::Update()
{

}

void doom::resource::Thread_Server::OnEndOfFrame()
{
}

void Thread_Server::WakeUpAllThreads()
{
	for (auto& thread : this->mManagedSubThreads)
	{
		if (thread.GetIsThreadSleeping() == true)
		{
			thread.PushBackJob(std::function<void()>()); // push dummy job
		}
	}
}

void Thread_Server::InitializeThreads()
{
	this->mMainThreadId = std::this_thread::get_id();

	for (auto& thread : this->mManagedSubThreads)
	{
		thread.SetPriorityWaitingTaskQueue(&(this->mPriorityWaitingTaskQueue));
	}

	this->bmIsInitialized = true;
}

void Thread_Server::DestroyThreads()
{
	for (auto& thread : this->mManagedSubThreads)
	{
		thread.TerminateThreadPool(true);
	}
	this->bmIsInitialized = false;
}

ThreadPool& doom::resource::Thread_Server::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}
