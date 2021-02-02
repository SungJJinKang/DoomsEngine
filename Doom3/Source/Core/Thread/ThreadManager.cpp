#include "ThreadManager.h"

#include "../Core.h"
#include "Thread.h"

using namespace doom::thread;

void doom::thread::ThreadManager::InitializeThreads()
{
	ThreadManager::mMainThreadId = std::this_thread::get_id();
	ThreadManager::mManagedSubThreads = new Thread[THREAD_COUNT];
	ThreadManager::bmIsInitialized = true;
}

void doom::thread::ThreadManager::DestroyThreads()
{
	delete[] ThreadManager::mManagedSubThreads;
	ThreadManager::bmIsInitialized = false;
}

doom::thread::Thread& doom::thread::ThreadManager::GetThread(size_t threadIndex)
{
	D_ASSERT(ThreadManager::bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
	return ThreadManager::mManagedSubThreads[threadIndex];
}
