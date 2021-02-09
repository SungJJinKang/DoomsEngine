#include "ThreadManager.h"

#include "../Core.h"
#include "Thread.h"

using namespace doom::resource;

void ThreadManager::Init()
{

}

void ThreadManager::Update()
{

}

void doom::resource::ThreadManager::OnEndOfFrame()
{
}

void ThreadManager::InitializeThreads()
{
	this->mMainThreadId = std::this_thread::get_id();
	this->mManagedSubThreads = new Thread[THREAD_COUNT];
	this->bmIsInitialized = true;
}

void ThreadManager::DestroyThreads()
{
	delete[] this->mManagedSubThreads;
	this->bmIsInitialized = false;
}

Thread& ThreadManager::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}
