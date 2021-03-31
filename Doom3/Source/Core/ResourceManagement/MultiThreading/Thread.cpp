#include "Thread.h"

void doom::resource::Thread::WorkerJob()
{
	while (true)
	{
		this->mIsThreadSleeping = true;

		if (this->mIsPoolTerminated == true)
		{
			return;
		}

		job_type newTask;
		
		if (this->mPriorityWaitingTaskQueue != nullptr)
		{// Check Priority Queue first
			this->mPriorityWaitingTaskQueue->try_dequeue(newTask); // try_dequeue don't block thread
		}

		if (!newTask)
		{
			this->mWaitingTaskQueue.wait_dequeue(newTask); // block thread until take element from queue
		}


		if (newTask)
		{
			this->mIsThreadSleeping = false;
#ifdef Thread_DEBUG
			std::cout << "Start New Task " << std::this_doom::resource::Thread::get_id() << std::endl;
#endif
			newTask();
		}
}
}

doom::resource::Thread::Thread() : mWaitingTaskQueue{}, mIsPoolTerminated{ false }, mIsThreadSleeping{ false }, mThread{ &doom::resource::Thread::WorkerJob, this }
{
#ifdef Thread_DEBUG
	std::cout << "Initializing Thread" << std::endl;
#endif
}

void doom::resource::Thread::TerminateThread(bool bIsBlockThread)
{
	if (mIsPoolTerminated)
		return;

#ifdef Thread_DEBUG
	std::cout << "Destructing Thread Pool" << std::endl;
#endif

	mIsPoolTerminated = true; // TO DOO : Should this eclosed by mutex, because sub thread can't see this variable changed

	//For stop queue, push dummy job ( i can't stop wait_dequeue, so make WorkerJob loop pushing dummy job )
	this->PushBackJob(job_type([]() {}));

	if (bIsBlockThread == true)
	{
		this->mThread.join(); // main thread will wait until sub thread finish it's last job
#ifdef Thread_DEBUG
		std::cout << "Thread is terminated" << std::endl;
#endif
	}
	else
	{
		this->mThread.detach();
#ifdef Thread_DEBUG
		std::cout << "Thread is detached" << std::endl;
#endif
	}

#ifdef Thread_DEBUG
	std::cout << "Thread is completely terminated" << std::endl;
	if (unsigned int lastJobs = this->mWaitingTaskQueue.size_approx() > 0)
	{
		std::cout << "but Thread Jobs remains : " << lastJobs << std::endl;
	}
#endif
}

doom::resource::Thread::~Thread()
{
	this->TerminateThread(true);
}

/// <summary>
/// This can be not inaccurate
/// </summary>
/// <returns></returns>
bool doom::resource::Thread::GetIsTerminated() const
{
	return this->mIsPoolTerminated;
}

/// <summary>
/// This can be not inaccurate
/// </summary>
/// <returns></returns>
bool doom::resource::Thread::GetIsThreadSleeping() const
{
	return this->mIsThreadSleeping;
}

size_t doom::resource::Thread::GetWaitingJobCount() const
{
	return mWaitingTaskQueue.size_approx();
}

void doom::resource::Thread::SetPriorityWaitingTaskQueue(BlockingConcurrentQueue<job_type>* queuePointer)
{
	this->mPriorityWaitingTaskQueue = queuePointer;
}
