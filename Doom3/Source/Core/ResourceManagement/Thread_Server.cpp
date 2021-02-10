#include "Thread_Server.h"

#include "../Core.h"
#include "Thread.h"

using namespace doom::resource;

void Thread_Server::Init()
{

}

void Thread_Server::Update()
{

}

void doom::resource::Thread_Server::OnEndOfFrame()
{
}

void Thread_Server::InitializeThreads()
{
	this->mMainThreadId = std::this_thread::get_id();
	this->mManagedSubThreads = new Thread[THREAD_COUNT];
	this->bmIsInitialized = true;
}

void Thread_Server::DestroyThreads()
{
	delete[] this->mManagedSubThreads;
	this->bmIsInitialized = false;
}

Thread& Thread_Server::GetThread(size_t threadIndex)
{
	D_ASSERT(this->bmIsInitialized == true);
	D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
	return this->mManagedSubThreads[threadIndex];
}
