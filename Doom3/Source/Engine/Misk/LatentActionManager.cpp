#include "LatentActionManager.h"

#include <ResourceManagement/Thread/RunnableThread/RunnableThread.h>

void dooms::LatentActionManager::Init(const int argc, char* const* const argv)
{
}

void dooms::LatentActionManager::Update()
{

}

void dooms::LatentActionManager::OnEndOfFrame()
{
	D_ASSERT(dooms::thread::IsInGameThread());

	moodycamel::BlockingConcurrentQueue<LATENT_ACTION_TYPE>& TargetLatentActionQueue = bLatentActionQueueToggle ? LatentActionQueue1 : LatentActionQueue2;

	LATENT_ACTION_TYPE LatentAction{};
	while (TargetLatentActionQueue.try_dequeue(LatentAction))
	{
		LatentAction();

		LatentAction = nullptr;
	}

	bLatentActionQueueToggle = !bLatentActionQueueToggle;
}
