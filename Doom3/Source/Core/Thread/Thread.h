#pragma once

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <future>

#include "../Core.h"

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
		private:
			bool mIsThreadDestructed;
			std::thread mThread;
			std::thread::id mThreadId;

			std::queue<std::function<void()>> WaitingTaskQueue;
			
			std::condition_variable ConditionVariable;
			std::mutex PoolMutex;

			~Thread();

			void WorkerJob();

			template<typename STD_FUNCTION>
			using return_type_of_std_function = typename STD_FUNCTION::result_type;

			template<typename Callable>
			using return_type_of_function_pointer = return_type_of_std_function < decltype(std::function{ std::declval<Callable>() }) > ;

		public:
			Thread(size_t poolSize);

			/// <summary>
			/// TerminateThread
			/// </summary>
			/// <param name="isBlock">Do block until thread is terminated??</param>
			void TerminateThread(bool isBlock);

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
			inline std::future<ReturnType> AddTaskTopPriority(const std::function<ReturnType()>& task)
			{
				D_ASSERT(this->mIsThreadDestructed == false);
			}

			template <typename ReturnType>
			inline std::future<ReturnType> AddTask(const std::function<ReturnType()>& task)
			{  
				D_ASSERT(this->mIsThreadDestructed == false);

				std::shared_ptr<std::promise<ReturnType>> promise{ new std::promise<ReturnType> };
				auto future = promise->get_future();

				std::function<void()> newTask = [promise, task = std::move(task)]()
				{
					if constexpr (!std::is_void_v<ReturnType>)
					{
						promise->set_value(task());
					}
					else
					{//if return type is void
						task();
						promise->set_value();
					}
				};

				{
					std::scoped_lock lock{ this->PoolMutex };
					WaitingTaskQueue.push(std::move(newTask)); //push new task to task queue
				}

				ConditionVariable.notify_one();

				return future;
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
			inline std::future<return_type_of_function_pointer<Function>> AddTaskTopPriority(Function&& f, Args&&... args)
			{
				D_ASSERT(this->mIsThreadDestructed == false);
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
			inline std::future<return_type_of_function_pointer<Function>> AddTask(Function&& f, Args&&... args)
			{
				D_ASSERT(this->mIsThreadDestructed == false);

				static_assert(std::is_invocable_v<Function, Args...>);
				std::function<return_type_of_function_pointer<Function>()> task = std::bind(std::forward<Function>(f), std::forward<Args>(args)...);
				return this->AddTask(task);

			}

			/// <summary>
			/// Add Multiple Task, This can reduce mutex lock cost(mutex lock is expensive)
			/// Tasks will be added at end of queue
			/// If tasks have different return type, pass std::function<void()> with reference variable as function argument ( example. std::bind(Function, int& result)  )
			/// </summary>
			template <typename ReturnType>
			std::vector<std::future<ReturnType>> AddTaskChunk(const std::vector<std::function<ReturnType()>>& tasks)
			{
				size_t taskCount = tasks.size();

				std::vector<std::shared_ptr<std::promise<ReturnType>>> promises{ taskCount };
				for (auto& promiseSharedPtr : promises)
				{
					promiseSharedPtr = { new std::promise<ReturnType> };
				}

				std::vector<std::future<ReturnType>> futures{ taskCount };
				for (size_t i = 0; i < promises.size(); i++)
				{
					futures[i] = promises[i]->get_future();
				}

				std::vector<std::function<void()>> taskContainer{  };
				taskContainer.reserve(taskCount);

				for (size_t i = 0; i < taskCount; i++)
				{
					std::function<void()> newTask = [promise = promises[i], task = std::move(tasks[i])]()
					{
						if constexpr (!std::is_void_v<ReturnType>)
						{
							promise->set_value(task());
						}
						else
						{//if return type is void
							task();
							promise->set_value();
						}
					};
					taskContainer.push_back(std::move(newTask));
				}

				{
					std::scoped_lock lock{ this->PoolMutex }; // Lock mutex just one time on multiple tasks
					for (auto& task : taskContainer)
					{
						this->WaitingTaskQueue.push(std::move(task)); //push new task to task queue
					}
				}
				ConditionVariable.notify_all();
				return futures;
			}



		};
	}
}
