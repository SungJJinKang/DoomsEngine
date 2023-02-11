#include "ThreadGlobal.h"

#include "RunnableThread/RunnableThread.h"

bool dooms::thread::IsInGameThread()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return (dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType() == EThreadType::GAME_THREAD);
}

bool dooms::thread::IsInRenderThread()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return (dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType() == EThreadType::RENDER_THREAD);
}

dooms::thread::EThreadType dooms::thread::GetLocalThreadType()
{
	D_ASSERT(dooms::thread::RunnableThread::GetThreadLocalRunnableThread() != nullptr);

	return dooms::thread::RunnableThread::GetThreadLocalRunnableThread()->GetThreadType();
}