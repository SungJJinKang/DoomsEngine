#pragma once

#include "../Core.h"

#include <functional>

#include "RunnableThread.h"
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <../Helper/Simple_SingleTon/Singleton.h>

#include "RenderThread.reflection.h"
namespace dooms
{
	namespace thread
	{
		class RenderCommand;

		class DOOM_API D_CLASS RenderThread : public RunnableThread, public ISingleton<RenderThread>
		{
			GENERATE_BODY()

		public:

			RenderThread();

			virtual eThreadType GetThreadType() const override;

			template<typename TSTR, typename LAMBDA>
			FORCE_INLINE void EnqueueRenderCommand(LAMBDA&& Lambda)
			{
				RenderCommandQueue.enqueue(std::forward<LAMBDA>(Lambda));
			}

			virtual const char* GetThreadName() const override;
			bool IsAllowMultipleThreadOfThisThreadType() const override;

		protected:
			
			virtual void Init_OnCallerThread() override;
			virtual void Tick_OnRunnableThread() override;
		
		private:

			moodycamel::BlockingConcurrentQueue<std::function<void()>> RenderCommandQueue;

		};
		

	}
}



#define ENQUEUE_RENDER_COMMAND(Type) \
	struct Type##Name \
	{  \
		static const char* CStr() { return #Type; } \
	}; \
	RenderThread::GetSingleton()->EnqueueRenderCommand<Type##Name>

