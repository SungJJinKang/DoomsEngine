#pragma once

#include <thread>
#include <queue>
#include <functional>
#include <future>

#include "../Core.h"
#include "Thread_Core.h"
#include <concurrentqueue/blockingconcurrentqueue.h>

namespace doom
{
	namespace resource
	{
		/// <summary>
		/// Thread class manage one thread.
		/// This class have Task(Job) queue.
		/// Pass Job(task) to this thread class.
		/// 
		/// </summary>
		class Thread
		{
			friend class Thread_Server;

		public:
			using thread_thread_job_type = typename std::function<void()>;

		private:
			std::atomic<bool> bmIsThreadDestructed;
			std::thread mThread;
			std::thread::id mThreadId;

			/// <summary>
			/// This is lock free queue
			/// 
			/// </summary>
			moodycamel::BlockingConcurrentQueue<thread_job_type> WaitingTaskQueue;
			static constexpr size_t QUEUE_INITIAL_RESERVED_SIZE = 30;
			
			Thread();
			~Thread();

			void WorkerJob();

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;



			template <typename ReturnType>
			thread_job_type _Make_Thread_Job(const std::shared_ptr<std::promise<ReturnType>>&& promise_shared_ptr, const std::function<ReturnType()>& task)
			{
				return thread_job_type([_promise_shared_ptr = std::move(promise_shared_ptr), task = task]()
				{
					if constexpr (!std::is_void_v<ReturnType>)
					{
						_promise_shared_ptr->set_value(task());
					}
					else
					{//if return type is void
						task();
						_promise_shared_ptr->set_value();
					}
				}
				);
			}
			template <typename ReturnType>
			thread_job_type _Make_Thread_Job(const std::shared_ptr<std::promise<ReturnType>>&& promise_shared_ptr, const std::function<ReturnType()>&& task)
			{
				return thread_job_type([_promise_shared_ptr = std::move(promise_shared_ptr), task = std::move(task)]()
				{
					if constexpr (!std::is_void_v<ReturnType>)
					{
						_promise_shared_ptr->set_value(task());
					}
					else
					{//if return type is void
						task();
						_promise_shared_ptr->set_value();
					}
				}
				);
			}

			template <typename ReturnType>
			inline std::future<ReturnType> _Enqueue_Job_Copy(const std::function<ReturnType()>& task, bool bIsPushAtFront)
			{
				std::shared_ptr<std::promise<ReturnType>> promise_shared_ptr{ new std::promise<ReturnType> };
				auto future = promise_shared_ptr->get_future();

				thread_job_type taskForTaskQueue = this->_Make_Std_Function_Copy(std::move(promise_shared_ptr), task);

				this->WaitingTaskQueue.enqueue(std::move(taskForTaskQueue));

				return future;
			}
			template <typename ReturnType>
			inline std::future<ReturnType> _Enqueue_Job_Move(const std::function<ReturnType()>&& task, bool bIsPushAtFront)
			{
				std::shared_ptr<std::promise<ReturnType>> promise_shared_ptr{ new std::promise<ReturnType> };
				auto future = promise_shared_ptr->get_future();

				thread_job_type taskForTaskQueue = this->_Make_Thread_Job(std::move(promise_shared_ptr), std::move(task));

				this->WaitingTaskQueue.enqueue(std::move(taskForTaskQueue));

				return future;
			}
			/// <summary>
			/// Add Multiple Task
			/// Tasks will be added at end of queue
			/// If tasks have different return type, pass thread_job_type with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> _Enqueue_Job_Chunk_Copy(const std::vector<std::function<ReturnType()>>& tasks, bool bIsPushAtFront)
			{
				size_t taskCount = tasks.size();

				std::vector<std::shared_ptr<std::promise<ReturnType>>> promise_shared_ptr_vector{};
				promise_shared_ptr_vector.reserve(taskCount);
				for (size_t i = 0; i < taskCount; i++)
				{
					promise_shared_ptr_vector.emplace_back(new std::promise<ReturnType>);
				}

				std::vector<std::future<ReturnType>> future_vector{};
				future_vector.reserve(taskCount);
				for (size_t i = 0; i < taskCount; i++)
				{
					future_vector.push_back(promise_shared_ptr_vector[i]->get_future());
				}

				std::vector<thread_job_type> taskContainer{  };
				taskContainer.reserve(taskCount);

				for (size_t i = 0; i < taskCount; i++)
				{
					taskContainer.push_back(_Make_Std_Function(std::move(promise_shared_ptr_vector[i]), tasks[i]));
				}

				this->WaitingTaskQueue.enqueue_bulk(taskContainer.begin(), taskCount); // enqueue_bulk will copy element ( bulk doesn't support move )
				/*
				for (size_t i = 0; i < taskCount; i++)
				{
					this->WaitingTaskQueue.enqueue(std::move(taskContainer[i]));
				}
				*/
				return future_vector;
			}

			template <typename ReturnType>
			std::vector<std::future<ReturnType>> _Enqueue_Job_Chunk_Move(const std::vector<std::function<ReturnType()>>&& tasks, bool bIsPushAtFront)
			{
				size_t taskCount = tasks.size();

				std::vector<std::shared_ptr<std::promise<ReturnType>>> promise_shared_ptr_vector{};
				promise_shared_ptr_vector.reserve(taskCount);
				for (size_t i = 0; i < taskCount; i++)
				{
					promise_shared_ptr_vector.emplace_back(new std::promise<ReturnType>);
				}

				std::vector<std::future<ReturnType>> future_vector{};
				future_vector.reserve(taskCount);
				for (size_t i = 0; i < taskCount; i++)
				{
					future_vector.push_back(promise_shared_ptr_vector[i]->get_future());
				}

				std::vector<thread_job_type> taskContainer{};
				taskContainer.reserve(taskCount);

				for (size_t i = 0; i < taskCount; i++)
				{
					taskContainer.push_back(_Make_Std_Function(std::move(promise_shared_ptr_vector[i]), std::move(tasks[i])));
				}

				this->WaitingTaskQueue.enqueue_bulk(std::make_move_iterator(taskContainer.begin()), taskCount); // enqueue_bulk will copy element ( bulk doesn't support move )
				/*
				for (size_t i = 0; i < taskCount; i++)
				{
					this->WaitingTaskQueue.enqueue(std::move(taskContainer[i]));
				}
				*/
				return future_vector;
			}

		public:
			

			/// <summary>
			/// TerminateThread
			/// </summary>
			/// <param name="isBlock">Do block until thread is terminated??</param>
			void TerminateThread(bool isDoBlock);

			bool operator==(const Thread& thread);
			bool operator==(const std::thread::id& threadId);

			Thread(const Thread&) = delete;
			Thread(Thread&&) noexcept = delete;
			Thread& operator=(const Thread&) = delete;
			Thread& operator=(Thread&&) noexcept = delete;

			



			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJob(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				return this->_Enqueue_Job_Copy(task, false);
			}
			template <typename ReturnType>
			inline std::future<ReturnType> PushBackJob(const std::function<ReturnType()>&& task)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				return this->_Enqueue_Job_Move(std::move(task), false);
			}

			/// <summary>
			/// push task to first(front) of queue
			/// this task will be executed firstly after job being executed end
			/// </summary>
			/// <typeparam name="Function"></typeparam>
			/// <typeparam name="...Args"></typeparam>
			/// <param name="f"></param>
			/// <param name="...args"></param>
			/// <returns></returns>
			template <typename Function, typename... Args>
			inline std::future<return_type_of_function_pointer<Function>> EmplaceBackJob(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				static_assert(std::is_invocable_v<Function, Args...>);
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->_Enqueue_Job_Move(std::move(task), true);

			}

			/// <summary>
			/// Add a task to job
			/// Task will be added at end of queue
			/// </summary>
			/// <typeparam name="Function"></typeparam>
			/// <typeparam name="...Args"></typeparam>
			/// <param name="f"></param>
			/// <param name="...args"></param>
			template <typename Function, typename... Args>
			inline std::future<return_type_of_function_pointer<Function>> EmplaceBackJob(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				static_assert(std::is_invocable_v<Function, Args...>);
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->_Enqueue_Job_Move(std::move(task), false);
			}

			
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> EmplaceBackJobChunk(std::vector<std::function<ReturnType()>>::iterator tasks, const size_t size)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				return this->_Enqueue_Job_Chunk_Copy(tasks, false);
			}
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> EmplaceBackJobChunk(std::move_iterator<std::vector<std::function<ReturnType()>>::iterator> tasks, const size_t size)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				return this->_Enqueue_Job_Chunk_Move(std::move(tasks), false);
			}
		};
	}
}
