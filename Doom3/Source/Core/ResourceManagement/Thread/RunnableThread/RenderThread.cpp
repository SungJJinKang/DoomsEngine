#include "RenderThread.h"

#include "../eThreadType.h"
#include <functional>

void dooms::thread::RenderThread::Init()
{
	RunnableThread::Init();
}

void dooms::thread::RenderThread::Tick()
{
	RunnableThread::Tick();

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
	: RunnableThread("Render Thread")
{
	
}

dooms::thread::eThreadType dooms::thread::RenderThread::GetThreadType() const
{
	return dooms::thread::eThreadType::RENDER_THREAD;
}
