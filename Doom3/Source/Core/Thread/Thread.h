#pragma once

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <future>

#include "../Core.h"
#include "../../Helper/concurrentqueue/blockingconcurrentqueue.h"

namespace doom
{
	namespace thread
	{
		/// <summary>
		/// Thread class manage one thread.
		/// This class have Task(Job) queue.
		/// Pass Job(task) to this thread class.
		/// 
		/// </summary>
		class Thread
		{
			friend class ThreadManager;
		private:
			bool bmIsThreadDestructed;
			std::thread mThread;
			std::thread::id mThreadId;

			/// <summary>
			/// This is lock free queue
			/// 
			/// </summary>
			moodycamel::BlockingConcurrentQueue<std::function<void()>> WaitingTaskQueue;
			static constexpr size_t QUEUE_INITIAL_RESERVED_SIZE = 30;
			
			Thread();
			~Thread();

			void WorkerJob();

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;



			template <typename ReturnType>
			std::function<void()> _Make_Std_Function(const std::shared_ptr<std::promise<ReturnType>>&& promise_shared_ptr, const std::function<ReturnType()>& task)
			{
				return std::function<void()>([_promise_shared_ptr = std::move(promise_shared_ptr), task = task]()
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
			std::function<void()> _Make_Std_Function(const std::shared_ptr<std::promise<ReturnType>>&& promise_shared_ptr, const std::function<ReturnType()>&& task)
			{
				return std::function<void()>([_promise_shared_ptr = std::move(promise_shared_ptr), task = std::move(task)]()
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
			inline std::future<ReturnType> _Enqueue(const std::function<ReturnType()>& task, bool bIsPushAtFront)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				std::shared_ptr<std::promise<ReturnType>> promise_shared_ptr{ new std::promise<ReturnType> };
				auto future = promise_shared_ptr->get_future();

				std::function<void()> taskForTaskQueue = this->_Make_Std_Function(std::move(promise_shared_ptr), task);

				this->WaitingTaskQueue.enqueue(std::move(taskForTaskQueue));

				return future;
			}
			template <typename ReturnType>
			inline std::future<ReturnType> _Enqueue(const std::function<ReturnType()>&& task, bool bIsPushAtFront)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				std::shared_ptr<std::promise<ReturnType>> promise_shared_ptr{ new std::promise<ReturnType> };
				auto future = promise_shared_ptr->get_future();

				std::function<void()> taskForTaskQueue = this->_Make_Std_Function(std::move(promise_shared_ptr), std::move(task));

				this->WaitingTaskQueue.enqueue(std::move(taskForTaskQueue));

				return future;
			}
			/// <summary>
			/// Add Multiple Task, This can reduce mutex lock cost(mutex lock is expensive)
			/// Tasks will be added at end of queue
			/// If tasks have different return type, pass std::function<void()> with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> _Enqueue_Chunk(const std::vector<std::function<ReturnType()>>& tasks, bool bIsPushAtFront)
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

				std::vector<std::function<void()>> taskContainer{  };
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
			std::vector<std::future<ReturnType>> _Enqueue_Chunk(const std::vector<std::function<ReturnType()>>&& tasks, bool bIsPushAtFront)
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

				std::vector<std::function<void()>> taskContainer{  };
				taskContainer.reserve(taskCount);

				for (size_t i = 0; i < taskCount; i++)
				{
					taskContainer.push_back(_Make_Std_Function(std::move(promise_shared_ptr_vector[i]), std::move(tasks[i])));
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

			// TODO : Support function pushing element at front of queue

			/// <summary>
			/// push task to first(front) of queue
			/// this task will be executed firstly after job being executed end
			/// </summary>
			/// <typeparam name="ReturnType"></typeparam>
			/// <param name="task"></param>
			/// <returns></returns>
			template <typename ReturnType>
			inline std::future<ReturnType> push_front(const std::function<ReturnType()>& task)
			{
				return this->_Enqueue(task, true);
			}
			template <typename ReturnType>
			inline std::future<ReturnType> push_front(const std::function<ReturnType()>&& task)
			{
				return this->_Enqueue(std::move(task), true);
			}

			template <typename ReturnType>
			inline std::future<ReturnType> push_back(const std::function<ReturnType()>& task)
			{
				return this->_Enqueue(task, false);
			}
			template <typename ReturnType>
			inline std::future<ReturnType> push_back(const std::function<ReturnType()>&& task)
			{
				return this->_Enqueue(std::move(task), false);
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
			inline std::future<return_type_of_function_pointer<Function>> emplace_front(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				static_assert(std::is_invocable_v<Function, Args...>);
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->_Enqueue(std::move(task), true);

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
			inline std::future<return_type_of_function_pointer<Function>> emplace_back(Function&& f, Args&&... args)
			{
				D_ASSERT(this->bmIsThreadDestructed == false);

				static_assert(std::is_invocable_v<Function, Args...>);
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->_Enqueue(std::move(task), false);

			}

			



		};
	}
}
