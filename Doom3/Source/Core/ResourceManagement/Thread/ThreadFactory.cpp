#include "ThreadFactory.h"

#include "RunnableThread/RunnableThread.h"

dooms::thread::RunnableThread* dooms::thread::ThreadFactory::CreateRunnableThread(const eThreadType TargetThreadType, const char* const BeautifulThreadName)
{
	dooms::thread::RunnableThread* CreatedRunnableThread = nullptr;

	switch (TargetThreadType)
	{
		case eThreadType::GAME_THREAD:
		{
			
			break;
		}
			
		case eThreadType::RENDER_THREAD:
		{

			break;
		}
			
		default:
		{
			D_ASSERT_LOG(false, "Unsupported Thread Type");
			break;
		}
	}

	D_ASSERT_LOG(CreatedRunnableThread == nullptr, "Fail to create RunnableThread");

	return CreatedRunnableThread;
}
