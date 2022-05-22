#pragma once

#include "../Core.h"

#include "RunnableThread.h"
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <../Helper/Simple_SingleTon/Singleton.h>

namespace dooms
{
	namespace thread
	{
		class RenderCommand;

		class DOOM_API D_CLASS RenderThread : public RunnableThread, public ISingleton<RenderThread>
		{

		private:

			moodycamel::BlockingConcurrentQueue<void()> RenderCommandQueue;

		protected:
			
			virtual void Init() override;
			virtual void Tick() override;

		public:
			
			RenderThread();

			virtual eThreadType GetThreadType() const override;

			template<typename TSTR, typename LAMBDA>
			FORCE_INLINE void EnqueueRenderCommand(LAMBDA&& Lambda)
			{
				RenderCommandQueue.enqueue(std::forward<LAMBDA>(Lambda));
			}
			
		};
		

	}
}



#define ENQUEUE_RENDER_COMMAND(Type) \
	struct Type##Name \
	{  \
		static const char* CStr() { return #Type; } \
	}; \
	RenderThread::GetSingleton()->EnqueueRenderCommand<Type##Name>

