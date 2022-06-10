#pragma once

#include "../Core.h"

#include <future>
#include <functional>
#include <type_traits>

#include <../Helper/Simple_SingleTon/Singleton.h>
#include <concurrentqueue/blockingconcurrentqueue.h>

#include "ThreadManager.h"

#include "JobPool.reflection.h"
namespace dooms
{
	namespace thread
	{
		class JobThread;

		class DOOM_API D_CLASS JobPool : public DObject, public ISingleton<JobPool>
		{
			GENERATE_BODY()

		public:

			using JOB_TYPE = std::function<void()>;
			
			template<typename LAMBDA>
			FORCE_INLINE void EnqueueJobToGlobalPool(LAMBDA&& JobLambda)
			{
				GlobalJobQueue.enqueue(std::forward<LAMBDA>(JobLambda));
				
				WakeUpJobThreads();
			}

			template<typename LAMBDA>
			auto EnqueueJobToGlobalPoolWithReturn(LAMBDA&& JobLambda)
			{
				using RETURN_TYPE = decltype(JobLambda());

				std::shared_ptr<std::promise<RETURN_TYPE>> ReturnPromise = std::make_shared<std::promise<RETURN_TYPE>>();
				
				std::future<RETURN_TYPE> ReturnFuture = ReturnPromise->get_future();

				EnqueueJobToGlobalPool
				(
					[Promise = ReturnPromise, Job = std::forward<LAMBDA>(JobLambda)]()
					{
						if constexpr(std::is_same_v<RETURN_TYPE, void>)
						{
							Promise->set_value();
						}
						else
						{
							Promise->set_value(Job());
						}
					}
				);

				WakeUpJobThreads();

				return std::move(ReturnFuture);
			}
			
			FORCE_INLINE bool TryDequeue(JOB_TYPE& Job)
			{
				return GlobalJobQueue.try_dequeue(Job);
			}

			INT32 GetJobThreadCount() const;

			void WakeUpJobThreads();

		private:
			
			moodycamel::BlockingConcurrentQueue<JobPool::JOB_TYPE> GlobalJobQueue;
		};

		template<typename LAMBDA>
		inline extern void ParallelFor(LAMBDA&& JobLambda, INT64 Count)
		{
			D_ASSERT(IsValid(JobPool::GetSingleton()));

			for(INT32 Index = 0 ; Index < Count ; Index++)
			{
				JobPool::GetSingleton()->EnqueueJobToGlobalPool(std::forward<LAMBDA>(JobLambda));
			}
		}

		template<typename LAMBDA>
		inline extern void ParallelFor(LAMBDA&& JobLambda)
		{
			ParallelFor(std::forward<LAMBDA>(JobLambda), dooms::thread::ThreadManager::GetSingleton()->GetRunnableThreadCount(eThreadType::JOB_THREAD));
		}

		template<typename LAMBDA>
		inline extern auto ParallelForWithReturn(LAMBDA&& JobLambda, INT64 Count)
		{
			D_ASSERT(IsValid(JobPool::GetSingleton()));

			using RETURN_TYPE = decltype(JobLambda());

			std::vector<std::future<RETURN_TYPE>> ReturnFutureList{};

			for (INT32 Index = 0; Index < Count; Index++)
			{
				std::future Future = JobPool::GetSingleton()->EnqueueJobToGlobalPoolWithReturn(std::forward<LAMBDA>(JobLambda));
				ReturnFutureList.emplace_back(std::move(Future));
			}

			return std::move(ReturnFutureList);
		}

		template<typename LAMBDA>
		inline extern auto ParallelForWithReturn(LAMBDA&& JobLambda)
		{
			return ParallelForWithReturn(std::forward<LAMBDA>(JobLambda), dooms::thread::ThreadManager::GetSingleton()->GetRunnableThreadCount(eThreadType::JOB_THREAD));
		}
	}
}
