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

				std::function<void()> newTask;
				this->WaitingTaskQueue.wait_dequeue(newTask);
				newTask();
			}
		}

		Thread::Thread()
			: mThread{ &Thread::WorkerJob, this }, mThreadId{ mThread.get_id() }, bmIsThreadDestructed{ false }, WaitingTaskQueue{ Thread::QUEUE_INITIAL_RESERVED_SIZE }
		{
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

			std::stringstream sstream;
			sstream << this->mThreadId;
			D_DEBUG_LOG({ "Destructing Thread : ", sstream.str() }, LogType::D_LOG);

			if (isDoBlock)
			{
				this->mThread.join();
			}
			else
			{
				this->mThread.detach();
			}
			

			D_DEBUG_LOG({ "Thread is destructed : ", sstream.str() }, LogType::D_LOG);
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