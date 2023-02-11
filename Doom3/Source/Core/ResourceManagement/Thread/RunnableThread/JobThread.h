#pragma once

#include <Core.h>

#include <functional>
#include <future>

#include "../EThreadType.h"
#include "RunnableThread.h"
#include "../JobPool.h"
#include <blockingconcurrentqueue.h>

#include "JobThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class JobPool;

		class DOOM_API D_CLASS JobThread : public RunnableThread
		{
			GENERATE_BODY()

		public:
			
			virtual EThreadType GetThreadType() const override;
			virtual const char* GetThreadName() const override;

			template<typename LAMBDA>
			FORCE_INLINE void EnqueueJob(LAMBDA&& JobLambda)
			{
				JobQueue.enqueue(std::forward<LAMBDA>(JobLambda));
			}

			template <typename RETURN_TYPE>
			std::future<RETURN_TYPE> EnqueueJobWithReturn(std::function<RETURN_TYPE()>&& InJob)
			{
				std::promise<RETURN_TYPE> ReturnPromise{};

				std::future<RETURN_TYPE> ReturnFuture = ReturnPromise.get_future();

				EnqueueJob
				(
					[ReturnPromise = std::move(ReturnPromise), Job = std::move(InJob)]()
					{
						ReturnPromise = Job();
					}
				);

				return ReturnFuture;
			}

			void SetJobPool(JobPool* InJobPool);
			bool IsAllowMultipleThreadOfThisThreadType() const override;

			void WakeUpRunnableThread() override;

		protected:

			virtual void InitFromCallerThread() override;
			virtual void InitFromRunnableThread() override;
			virtual void TickFromRunnableThread() override;
			EThreadPriority GetRecommendedPriorityOfThreadType() const override;

		private:

			moodycamel::BlockingConcurrentQueue<JobPool::JOB_TYPE> JobQueue;

			D_PROPERTY()
			JobPool* JobPool = nullptr;

		};
	}
}
