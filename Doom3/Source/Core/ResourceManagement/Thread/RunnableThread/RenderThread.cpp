#include "RenderThread.h"

#include "../eThreadType.h"
#include <functional>

#include "RunnableThread.h"

void dooms::thread::RenderThread::FlushRenderCommandQueue()
{
	while(RenderCommandQueue.size_approx() != 0)
	{
		std::this_thread::yield();
	}
}

const char* dooms::thread::RenderThread::GetThreadName() const
{
	return "RenderThread";
}

bool dooms::thread::RenderThread::IsAllowMultipleThreadOfThisThreadType() const
{
	return false;
}

void dooms::thread::RenderThread::WakeUpRunnableThread()
{
	Base::WakeUpRunnableThread();

	EnqueueRenderCommand([]() {});
}

void dooms::thread::RenderThread::Init_OnCallerThread()
{
	RunnableThread::Init_OnCallerThread();
}

void dooms::thread::RenderThread::Tick_OnRunnableThread()
{
	RunnableThread::Tick_OnRunnableThread();

	std::function<void()> RenderTask{};

	RenderCommandQueue.try_dequeue(RenderTask); // try_dequeue don't block thread

	if (static_cast<bool>(RenderTask) == false)
	{
		RenderCommandQueue.wait_dequeue(RenderTask); // block thread until take element from queue
	}
	
	if (static_cast<bool>(RenderTask) == true)
	{
		RenderTask();
	}
}

dooms::thread::RenderThread::RenderThread()
{
	
}

dooms::thread::eThreadType dooms::thread::RenderThread::GetThreadType() const
{
	return dooms::thread::eThreadType::RENDER_THREAD;
}
