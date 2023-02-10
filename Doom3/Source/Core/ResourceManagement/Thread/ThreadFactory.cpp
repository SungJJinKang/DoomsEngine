#include "ThreadFactory.h"

#include "RunnableThread/RunnableThread.h"
#include "RunnableThread/GameThread.h"
#include "RunnableThread/RenderThread.h"
#include "RunnableThread/JobThread.h"

dooms::thread::RunnableThread* dooms::thread::ThreadFactory::CreateRunnableThread(const EThreadType TargetThreadType)
{
	dooms::thread::RunnableThread* CreatedRunnableThread = nullptr;

	switch (TargetThreadType)
	{
		case EThreadType::GAME_THREAD:
		{
			CreatedRunnableThread = dooms::CreateDObject<GameThread>();
			break;
		}
			
		case EThreadType::RENDER_THREAD:
		{
			CreatedRunnableThread = dooms::CreateDObject<RenderThread>();
			break;
		}

		case EThreadType::JOB_THREAD:
		{
			CreatedRunnableThread = dooms::CreateDObject<JobThread>();
			break;
		}
			
		default:
		{
			D_ASSERT_LOG(false, "Unsupported Thread Type");
			break;
		}
	}

	D_ASSERT_LOG(CreatedRunnableThread != nullptr, "Fail to create RunnableThread");

	return CreatedRunnableThread;
}
