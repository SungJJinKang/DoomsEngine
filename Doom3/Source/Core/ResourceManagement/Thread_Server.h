#pragma once

#include <array>
#include <thread>

#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

#include "Thread_Core.h"
#include <concurrentqueue/blockingconcurrentqueue.h>

#define THREAD_COUNT (5)

namespace doom
{
	namespace resource
	{
		class Thread;
		/// <summary>
		/// ThreadManager manage threads
		/// Never make thread without this ThreadManager class
		/// Thread count is limited to THREAD_COUNT
		/// 
		/// 
		/// Each Thread have a role
		/// So Use GetThread(index) function and GetReference thread reference and Pass Task!!!!
		/// </summary>
		class Thread_Server : public IGameFlow, public ISingleton<Thread_Server>
		{

		private:
			std::thread::id mMainThreadId{};
			Thread* mManagedSubThreads{ nullptr };
			bool bmIsInitialized{ false };

			/// <summary>
			/// Waiting Task Queue.
			/// This
			/// </summary>
			moodycamel::BlockingConcurrentQueue<thread_job_type> WaitingTaskQueue;

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

		public:
			void InitializeThreads();
			void DestroyThreads();
			Thread& GetThread(size_t threadIndex);
	

		};
	}
}


