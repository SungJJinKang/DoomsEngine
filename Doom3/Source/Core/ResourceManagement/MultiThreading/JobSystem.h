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

			unsigned int MAX_SUB_THREAD_COUNT{};
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

			void SetMemoryBarrierOnAllSubThreads();
	
			template <typename ReturnType>
			std::future<ReturnType> PushBackJobToPriorityQueue(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto pair = _MakeThreadJob(task);
				this->mPriorityWaitingTaskQueue.enqueue(std::move(pair.first)); //push new task to task queue

				this->WakeUpAllSubThreads();
				return std::move(pair.second);
			}
			template <typename ReturnType>
			std::future<ReturnType> PushBackJobToPriorityQueue(std::function<ReturnType()>&& task)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto pair = _MakeThreadJob(std::move(task));
				this->mPriorityWaitingTaskQueue.enqueue(std::move(pair.first)); //push new task to task queue

				this->WakeUpAllSubThreads();
				return std::move(pair.second);
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToPriorityQueue(const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto pair = Thread::_MakeThreadJobChunk(tasks);
				this->mPriorityWaitingTaskQueue.enqueue_bulk(std::make_move_iterator(pair.first.begin()), pair.first.size());
				this->WakeUpAllSubThreads();
				return std::move(pair.second);
			}
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToPriorityQueue(std::vector<std::function<ReturnType()>>&& tasks)
			{
				D_ASSERT(this->bmIsInitialized == true);

				auto pair = Thread::_MakeThreadJobChunk(std::move(tasks));
				this->mPriorityWaitingTaskQueue.enqueue_bulk(std::make_move_iterator(pair.first.begin()), pair.first.size());
				this->WakeUpAllSubThreads();
				return std::move(pair.second);
			}
			//

			template <typename ReturnType>
			inline void PushBackJobToAllThread(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->bmIsInitialized == true);

				for (unsigned int i = 0; i < SUB_THREAD_COUNT; i++)
				{
					this->mManagedSubThreads[i].PushBackJob(task);
				}
			}

			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJobToSpecificThread(size_t threadIndex, const std::function<ReturnType()>& task)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJob(task);
			}
			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJobToSpecificThread(size_t threadIndex, std::function<ReturnType()>&& task)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJob(std::move(task));
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
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunkToSpecificThread(size_t threadIndex, std::vector<std::function<ReturnType()>>&& tasks)
			{
				D_ASSERT(threadIndex >= 0 && threadIndex < SUB_THREAD_COUNT);
				D_ASSERT(this->bmIsInitialized == true);

				return this->mManagedSubThreads[threadIndex].PushBackJobChunk(std::move(tasks));
			}
		};
	}
}

///Check current statement is called on MainThread
#define CHECK_IS_EXECUTED_ON_MAIN_THREAD D_ASSERT(doom::resource::JobSystem::GetSingleton()->GetMainThreadID() == std::this_thread::get_id())

