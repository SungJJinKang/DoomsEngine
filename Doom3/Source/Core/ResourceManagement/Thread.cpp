#include "Thread.h"

#include <sstream>

namespace doom
{
	namespace resource
	{

		

		void Thread::WorkerJob()
		{
			while (true)
			{
				//lck Lock
				if (this->bmIsThreadDestructed)
				{
					// exit thread
					return;
				}

			
				thread_job_type newTask;
				this->WaitingTaskQueue.wait_dequeue(newTask);
				if (newTask)
				{
					newTask();
				}
				
			}
		}

		Thread::Thread()
			: mThread{ &Thread::WorkerJob, this }, mThreadId{ mThread.get_id() }, bmIsThreadDestructed{ false }, WaitingTaskQueue{ Thread::QUEUE_INITIAL_RESERVED_SIZE }
		{
			D_ASSERT(this->WaitingTaskQueue.is_lock_free() == true);
		}


		Thread::~Thread()
		{
			this->TerminateThread(true);
		}

		void Thread::TerminateThread(bool isDoBlock)
		{
			if (bmIsThreadDestructed)
				return;

			bmIsThreadDestructed = true;
			std::function<void()> dummyFunction{ []() {} };
			this->PushBackJob(dummyFunction);

			std::stringstream sstream;
			sstream << this->mThreadId;
			D_DEBUG_LOG({ "Destructing Thread : ", sstream.str() }, eLogType::D_LOG);

			if (isDoBlock)
			{
				this->mThread.join();
			}
			else
			{
				this->mThread.detach();
			}
			

			D_DEBUG_LOG({ "Thread is destructed : ", sstream.str() }, eLogType::D_LOG);
		}

		bool Thread::operator==(const Thread& thread)
		{
			return this->mThreadId == thread.mThreadId;
		}

		bool Thread::operator==(const std::thread::id& threadId)
		{
			return this->mThreadId == threadId;
		}

	}
}