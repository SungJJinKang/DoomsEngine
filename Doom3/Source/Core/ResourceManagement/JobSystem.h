#pragma once

#include <array>
#include <thread>
#include <utility>
#include <memory>

#include "../Core.h"
#include "../Game/IGameFlow.h"

#include "Thread_Core.h"
#include "Thread.h"
#include <concurrentqueue/blockingconcurrentqueue.h>
using namespace moodycamel;




namespace doom
{
	class GameCore;
	namespace resource
	{
		//TODO : Thread가 쉬는지 일하는지 확인할 수 있게 Profiling 기능 추가

		class Thread;
		/// <summary>
		/// https://www.youtube.com/watch?v=M1e9nmmD3II
		/// Job Stealing 구현, 맵리듀스, 균등하게 스레드에 job나눠주기
		/// 
		/// 
		/// 
		/// 
		/// ThreadManager manage threads
		/// Never make thread without this ThreadManager class
		/// Thread count is limited to THREAD_COUNT
		/// 
		/// 
		/// Each Thread have a role
		/// So Use GetThread(index) function and GetReference thread reference and Pass Task!!!!
		/// </summary>
		class JobSystem : public IGameFlow, public ISingleton<JobSystem>
		{
			friend class ::doom::GameCore;

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;

		private:
			std::thread::id mMainThreadId{};

			unsigned int SUB_THREAD_COUNT{};
			std::unique_ptr<Thread[]> mManagedSubThreads{};
			bool bmIsInitialized{ false };

			/// <summary>
			/// Priority Waiting Task Queue.
			/// Every sub threads check this mPriorityWaitingTaskQueue before their's own waiting queue
			/// </summary>
			BlockingConcurrentQueue<Thread::job_type> mPriorityWaitingTaskQueue{};

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			/// <summary>
			/// Use this function To WakeUp sleeping threads
			/// </summary>
			void WakeUpAllSubThreads();

			/// <summary>
			/// return reference of Sleeping Thread
			/// if every thread is working, return thread having fewest waiting job count
			/// </summary>
			/// <returns></returns>
			Thread& GetSleepingSubThread() const;

			void InitializeSubThreads();
			void DestroySubThreads();
			/// <summary>
			/// Don't use this
			/// </summary>
			/// <param name="threadIndex"></param>
			/// <returns></returns>
			[[deprecated]] Thread& GetThread(size_t threadIndex);

		public:
			
			virtual ~JobSystem();

			std::thread::id GetMainThreadID() const;
	
			template <typename ReturnType>
			std::future<ReturnType> PushBackJobToAnySleepingThread(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto future = this->GetSleepingSubThread().PushBackJob(this->mPriorityWaitingTaskQueue, task);
				this->WakeUpAllSubThreads();
				return future;
			}

			template <typename Function, typename... Args>
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJobToAnySleepingThread(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto future = this->GetSleepingSubThread().EmplaceBackJob(this->mPriorityWaitingTaskQueue, std::forward<Function>(f), std::forward<Function>(args)...);
				this->WakeUpAllSubThreads();
				return future;
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToAnySleepingThread(const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto futures = this->GetSleepingSubThread().PushBackJobChunk(this->mPriorityWaitingTaskQueue, tasks);
				this->WakeUpAllSubThreads();
				return futures;
			}

			//

			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJobToSpecificThread(size_t threadIndex, const std::function<ReturnType()>& task)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJob(task);
			}

			template <typename Function, typename... Args>
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJobToSpecificThread(size_t threadIndex, Function&& f, Args&&... args)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].EmplaceBackJob(std::forward<Function>(f), std::forward<Args>(args)...);
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToSpecificThread(size_t threadIndex, const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJobChunk(tasks);
			}
		};
	}
}

///Check current statement is called on MainThread
#define CHECK_IS_EXECUTED_ON_MAIN_THREAD D_ASSERT(doom::resource::JobSystem::GetSingleton()->GetMainThreadID() == std::this_thread::get_id())

