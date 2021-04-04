#include "JobSystem.h"

#include <limits>

#include "../Core.h"
#include "Thread.h"

using namespace doom::resource;

void JobSystem::Init()
{
	JobSystem::SUB_THREAD_COUNT = math::Max(MAX_SUB_THREAD_COUNT, std::thread::hardware_concurrency() - 1); // Set core count - 1 to  sub thread count 
	this->InitializeSubThreads();
}

void JobSystem::Update()
{

}

void doom::resource::JobSystem::OnEndOfFrame()
{
}


void JobSystem::WakeUpAllSubThreads()
{
	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].PushBackJob(std::function<void()>()); // push dummy job
	}
}

void JobSystem::InitializeSubThreads()
{
	this->mMainThreadId = std::this_thread::get_id();

	this->mManagedSubThreads = std::make_unique<Thread[]>(SUB_THREAD_COUNT);
	

	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].SetPriorityWaitingTaskQueue(&(this->mPriorityWaitingTaskQueue));
	}

	this->bmIsInitialized = true;
}

void JobSystem::DestroySubThreads()
{
	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].TerminateThread(true); // main thread wait until sub threads finish their last job
	}
	this->bmIsInitialized = false;
}

Thread& doom::resource::JobSystem::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}

void JobSystem::SetMemoryBarrierOnAllSubThreads()
{
	for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
	{
		this->mManagedSubThreads[i].SetMemoryBarrier();
	}
}

std::thread::id JobSystem::GetMainThreadID() const
{
	return this->mMainThreadId;
}

JobSystem::~JobSystem()
{
	this->DestroySubThreads();
}