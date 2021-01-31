#include "Thread.h"

#include <sstream>

namespace doom
{
	namespace thread
	{

		

		void Thread::WorkerJob()
		{
			while (true)
			{
				std::unique_lock<std::mutex> lck{ this->PoolMutex };
				this->ConditionVariable.wait(lck, [this]() {return !this->WaitingTaskQueue.empty() || this->mIsThreadDestructed; });
				//lck Lock
				if (this->mIsThreadDestructed)
				{
					// exit thread
					return;
				}
				if (this->WaitingTaskQueue.empty())
				{
					lck.unlock();
					continue; // still Task Queue is empty
				}


				auto task = this->WaitingTaskQueue.front();
				this->WaitingTaskQueue.pop();
				lck.unlock();

				//std::cout << "Start New Task " << std::this_thread::get_id() << std::endl;
				//D_DEBUG_LOG()
				

				task();
			}
		}

		Thread::Thread(size_t poolSize)
			: mThread{ &Thread::WorkerJob, this }, mThreadId{ mThread.get_id() }, mIsThreadDestructed{ false }, WaitingTaskQueue{}, ConditionVariable{}, PoolMutex{}
		{
		}

		Thread::~Thread()
		{
			this->TerminateThread(true);
		}

		void Thread::TerminateThread(bool isBlock)
		{
			if (mIsThreadDestructed)
				return;

			mIsThreadDestructed = true;

			std::stringstream sstream;
			sstream << this->mThreadId;
			D_DEBUG_LOG({ "Destructing Thread : ", sstream.str() }, LogType::D_LOG);

			ConditionVariable.notify_all();

			if (isBlock)
			{
				this->mThread.join();
			}
			else
			{
				this->mThread.detach();
			}
			

			D_DEBUG_LOG({ "Thread is destructed : ", sstream.str() }, LogType::D_LOG);
		}

	}
}