#pragma once

#include <vector>

#include <thread>
#include <future>

#include <cassert>

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
			job_type MakeThreadJob(const std::shared_ptr<std::promise<ReturnType>>&& promise_shared_ptr, const std::function<ReturnType()>& task)
			{
				return job_type([_promise_shared_ptr = std::move(promise_shared_ptr), task = std::move(task)]() // if task's wrapped object has move constructor, it will be moved. if not, it will be copyed
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
				}
				);
			}

			void WorkerJob();

			template <typename ReturnType>
			inline std::future<ReturnType> _Push_Back_Job(BlockingConcurrentQueue<job_type>& queue, const std::function<ReturnType()>& task)
			{
				std::shared_ptr<std::promise<ReturnType>> promise_ptr{ new std::promise<ReturnType> };
				auto future = promise_ptr->get_future();

				queue.enqueue(Thread::MakeThreadJob(std::move(promise_ptr), task)); //push new task to task queue

				return future;
			}

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;

		public:

			/*
			Thread(std::thread** pointerOfThreadArray, size_t mPoolSize)
				: mPoolSize{ mPoolSize }, mWaitingTaskQueue{}, mIsPoolTerminated{ false }
			{
				assert(mPoolSize > 0);

				*pointerOfThreadArray = new std::thread[this->mPoolSize];
				this->mThreadWorkers = *pointerOfThreadArray;

				for (size_t i = 0; i < mPoolSize; i++)
				{
		#ifdef Thread_DEBUG
					std::cout << "Initializing mThreadWorkers(Threads)" << std::endl;
		#endif
					this->mThreadWorkers[i] = std::thread{ &Thread::WorkerJob, this };
				}

			}
			*/

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
			inline std::future<ReturnType> PushBackJob(BlockingConcurrentQueue<job_type>& queue, const std::function<ReturnType()>& task)
			{
				return this->_Push_Back_Job(queue, task);
			}

			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJob(const std::function<ReturnType()>& task)
			{
				assert(this->mIsPoolTerminated == false);

				return this->PushBackJob(this->mWaitingTaskQueue, task);
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
			std::future<return_type_of_function_pointer<Function>> EmplaceBackJob(BlockingConcurrentQueue<job_type>& queue, Function&& f, Args&&... args)
			{
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->_Push_Back_Job(queue, task);

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
				assert(this->mIsPoolTerminated == false);

				return this->EmplaceBackJob(this->mWaitingTaskQueue, std::forward<Function>(f), std::forward<Args>(args)...);

			}

			/// <summary>
			/// Add Multiple Task
			/// 
			/// If tasks have different return type, pass job_type with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunk(BlockingConcurrentQueue<job_type>& queue, const std::vector<std::function<ReturnType()>>& tasks)
			{
				size_t size = tasks.size();

				std::vector<std::shared_ptr<std::promise<ReturnType>>> promise_ptr_vec{};
				promise_ptr_vec.reserve(size);
				for (size_t i = 0; i < size; i++)
				{
					promise_ptr_vec.emplace_back(new std::promise<ReturnType>());
				}

				std::vector<std::future<ReturnType>> future_vec{};
				future_vec.reserve(size);
				for (size_t i = 0; i < size; i++)
				{
					future_vec.push_back(promise_ptr_vec[i]->get_future());
				}

				std::vector<job_type> taskContainer{};
				taskContainer.reserve(size);

				for (size_t i = 0; i < size; i++)
				{
					taskContainer.push_back(Thread::MakeThreadJob(std::move(promise_ptr_vec[i]), tasks[i]));
				}

				queue.enqueue_bulk(std::make_move_iterator(taskContainer.begin()), taskContainer.size()); //push new task to task queue
				return future_vec;
			}

			/// <summary>
			/// Add Multiple Task
			/// 
			/// If tasks have different return type, pass job_type with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> PushBackJobChunk(const std::vector<std::function<ReturnType()>>& tasks)
			{
				assert(this->mIsPoolTerminated == false);

				return this->PushBackJobChunk(this->mWaitingTaskQueue, tasks);
			}


		};

	}
}