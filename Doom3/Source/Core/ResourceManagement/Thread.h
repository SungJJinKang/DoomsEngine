#pragma once

#include <vector>

#include <thread>
#include <future>

#include "../Core.h"
#include <concurrentqueue/blockingconcurrentqueue.h>
using namespace moodycamel;
//#define Thread_DEBUG // FOR MONITORING
#ifdef Thread_DEBUG
#include <iostream>
#endif

namespace doom
{
	namespace resource
	{

		/// <summary>
		//
		//	THREAD POOL
		//	Features : Header Only, C++17
		//	HOW TO USE : SEE eample.cpp FILE
		//  
		//
		//	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//	WARNING : 
		//	Don't Release Thread Pool Instance before Every Waiting Tasks is finished.
		//	If You do, Thread Pool's Job will be terminated Immediately After Each Thread finish the task what it's doing
		//	So If Thread Pool still have unfinished Task, it will be abandoned
		//
		//
		/// references : https://en.wikipedia.org/wiki/Thread_pool
		/// </summary>
		class Thread
		{
			friend class JobSystem;
		public:
			using job_type = typename std::function<void()>;

		private:
			bool mIsPoolTerminated;
			bool mIsThreadSleeping;

			/// <summary>
			/// Maintain Thread Life Until Thread instace will be destructed
			/// Why use concurrent Queue ? : Any thread can push job
			/// </summary>
			std::thread mThread;
			BlockingConcurrentQueue<job_type> mWaitingTaskQueue;

			BlockingConcurrentQueue<job_type>* mPriorityWaitingTaskQueue{ nullptr };

			template <typename ReturnType>
			static std::pair<job_type, std::future<ReturnType>> _MakeThreadJob(const std::function<ReturnType()>& task)
			{
				std::shared_ptr<std::promise<ReturnType>> promise_ptr{ new std::promise<ReturnType> };
				auto future = promise_ptr->get_future();

				return {
					job_type([_promise_shared_ptr = std::move(promise_ptr), task = task]() // if task's wrapped object has move constructor, it will be moved. if not, it will be copyed
					{
					if constexpr (!std::is_void_v<ReturnType>)
					{
						assert(task); // task having return type should be valid
						_promise_shared_ptr->set_value(task());
					}
					else
					{//if return type is void
						if (task)
						{
							task();
						}
						_promise_shared_ptr->set_value();
					}
					})
					,
					std::move(future) };
			}

			template <typename ReturnType>
			static std::pair<job_type, std::future<ReturnType>> _MakeThreadJob(std::function<ReturnType()>&& task)
			{
				std::shared_ptr<std::promise<ReturnType>> promise_ptr{ new std::promise<ReturnType> };
				auto future = promise_ptr->get_future();

				return {
					job_type([_promise_shared_ptr = std::move(promise_ptr), task = std::move(task)]() // if task's wrapped object has move constructor, it will be moved. if not, it will be copyed
					{
					if constexpr (!std::is_void_v<ReturnType>)
					{
						assert(task); // task having return type should be valid
						_promise_shared_ptr->set_value(task());
					}
					else
					{//if return type is void
						if (task)
						{
							task();
						}
						_promise_shared_ptr->set_value();
					}
					})
					,
					std::move(future) };
			}

			template <typename ReturnType>
			static std::pair<std::vector<job_type>, std::vector<std::future<ReturnType>>>  _MakeThreadJobChunk(const std::vector<std::function<ReturnType()>>& tasks)
			{
				std::pair<std::vector<job_type>, std::vector<std::future<ReturnType>>> pairs{};
				pairs.first.reserve(tasks.size());
				pairs.second.reserve(tasks.size());
				for (size_t i = 0; i < tasks.size(); i++)
				{
					auto pair = Thread::_MakeThreadJob(tasks[i]); 
					pairs.first.push_back(std::move(pair.first)); // why move ? job type will be created in _MakeThreadJob
					pairs.second.push_back(std::move(pair.second));
				}

				return pairs;
			}
			template <typename ReturnType>
			static std::pair<std::vector<job_type>, std::vector<std::future<ReturnType>>>  _MakeThreadJobChunk(std::vector<std::function<ReturnType()>>&& tasks)
			{
				std::pair<std::vector<job_type>, std::vector<std::future<ReturnType>>> pairs{};
				pairs.first.reserve(tasks.size());
				pairs.second.reserve(tasks.size());
				for (size_t i = 0; i < tasks.size(); i++)
				{
					auto pair = Thread::_MakeThreadJob(std::move(tasks[i]));
					pairs.first.push_back(std::move(pair.first)); // why move ? job type will be created in _MakeThreadJob
					pairs.second.push_back(std::move(pair.second));
				}

				return pairs;
			}

			void WorkerJob();

		

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;

		public:

		

			Thread();


			Thread(const Thread&) = delete;
			Thread(Thread&&) noexcept = default;

			Thread& operator=(const Thread&) = delete;
			Thread& operator=(Thread&&) noexcept = default;

			/// <summary>
			/// Terminate Thread.
			/// Every Threads(mThreadWorkers) will be terminated
			/// Caller thread will be blocked until All threads finished the job it doing.
			/// And if Unfinished Jobs remains, they will be abandoned
			/// </summary>
			/// <param name="bIsBlockThread">Do block current thread until thread finish job it doing</param>
			void TerminateThread(bool bIsBlockThread);

			/// <summary>
			/// Terminate Thread.
			/// Every Threads(mThreadWorkers) will be terminated
			/// Caller thread will be blocked until All threads finished the job it doing.
			/// And if Unfinished Jobs remains, they will be abandoned
			/// </summary>
			~Thread();


			bool GetIsTerminated() const;

			bool GetIsThreadSleeping() const;

			size_t GetWaitingJobCount() const;

			void SetPriorityWaitingTaskQueue(BlockingConcurrentQueue<job_type>* queuePointer);

			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJob(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->mIsPoolTerminated == false);

				auto pair = _MakeThreadJob(task);
				this->mWaitingTaskQueue.enqueue(std::move(pair.first)); // why move ? job type will be created in _MakeThreadJob
				return std::move(pair.second);
			}
			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJob(std::function<ReturnType()>&& task)
			{
				D_ASSERT(this->mIsPoolTerminated == false);

				auto pair = _MakeThreadJob(std::move(task));
				this->mWaitingTaskQueue.enqueue(std::move(pair.first));
				return std::move(pair.second);
			}


			/// <summary>
			/// Pass
			/// Don't use placeholder
			/// 
			/// if you want pass by reference, pass with std::ref!!!!!!!!
			/// </summary>
			/// <typeparam name="Function"></typeparam>
			/// <typeparam name="...Args"></typeparam>
			/// <param name="f"></param>
			/// <param name="...args"></param>
			template <typename Function, typename... Args>
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJob(Function&& f, Args&&... args)
			{
				D_ASSERT(this->mIsPoolTerminated == false);

				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->PushBackJob(std::move(task));
			}


			/// <summary>
			/// Add Multiple Task
			/// 
			/// If tasks have different return type, pass job_type with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunk(const std::vector<std::function<ReturnType()>>& tasks)
			{
				D_ASSERT(this->mIsPoolTerminated == false);

				auto pair = _MakeThreadJobChunk(std::move(tasks)); // why move ? job type will be created in _MakeThreadJob
				this->mWaitingTaskQueue.enqueue_bulk(std::make_move_iterator(pair.first.begin()), pair.first.size()); //push new task to task queue
				return std::move(pair.second);
			}
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunk(std::vector<std::function<ReturnType()>>&& tasks)
			{
				D_ASSERT(this->mIsPoolTerminated == false);

				auto pair = _MakeThreadJobChunk(std::move(tasks));

				this->mWaitingTaskQueue.enqueue_bulk(std::make_move_iterator(pair.first.begin()), pair.first.size()); //push new task to task queue
				return std::move(pair.second);
			}

		};

	}
}