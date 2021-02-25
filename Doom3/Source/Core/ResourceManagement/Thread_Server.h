#pragma once

#include <array>
#include <thread>
#include <utility>

#include "../../Helper/Singleton.h"
#include "../Game/IGameFlow.h"

#include "Thread_Core.h"
#include <concurrentqueue/blockingconcurrentqueue.h>
using namespace moodycamel;

#include <ThreadPool_Cpp/ThreadPool.h>

#define THREAD_COUNT (6)

namespace doom
{
	class GameCore;
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
			friend class ::doom::GameCore;

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;

		private:
			std::thread::id mMainThreadId{};
			std::array<ThreadPool, THREAD_COUNT> mManagedSubThreads{};
			bool bmIsInitialized{ false };

			/// <summary>
			/// Priority Waiting Task Queue.
			/// Every sub threads check this mPriorityWaitingTaskQueue before their's own waiting queue
			/// </summary>
			BlockingConcurrentQueue<ThreadPool::job_type> mPriorityWaitingTaskQueue{};

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			/// <summary>
			/// Use this function To WakeUp sleeping threads
			/// </summary>
			void WakeUpAllThreads();

		public:
			void InitializeThreads();
			void DestroyThreads();
			ThreadPool& GetThread(size_t threadIndex);
	
			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJobToAnySleepingThread(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->bmIsInitialized == true);

				this->WakeUpAllThreads();
				return ThreadPool::PushBackJob(this->mPriorityWaitingTaskQueue, task);
			}

			template <typename Function, typename... Args>
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJobToAnySleepingThread(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsInitialized == true);

				this->WakeUpAllThreads();
				return ThreadPool::EmplaceBackJob(this->mPriorityWaitingTaskQueue, std::forward<Function>(f), std::forward<Function>(args)...);
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToAnySleepingThread(const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(this->bmIsInitialized == true);

				this->WakeUpAllThreads();
				return ThreadPool::PushBackJobChunk(this->mPriorityWaitingTaskQueue, tasks);
			}

			//

			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJobToSpecificThread(size_t threadIndex, const std::function<ReturnType()>& task)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJob(task);
			}

			template <typename Function, typename... Args>
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJobToSpecificThread(size_t threadIndex, Function&& f, Args&&... args)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].EmplaceBackJob(std::forward<Function>(f), std::forward<Args>(args)...);
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToSpecificThread(size_t threadIndex, const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJobChunk(tasks);
			}
		};
	}
}


