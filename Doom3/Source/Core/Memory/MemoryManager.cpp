#include "MemoryManager.h"

#include <oneapi/tbb/tbbmalloc_proxy.h>


void dooms::memory::MemoryManager::CheckIsIntelTBBLoaded() const
{
	char** tbbLog;
	const int isTbbSuccess = TBB_malloc_replacement_log(&tbbLog);
	D_ASSERT_LOG(isTbbSuccess == 0, *tbbLog);
	if(isTbbSuccess == 0)
	{
		D_RELEASE_LOG(eLogType::D_LOG, "Intel TBB is successfully loaded ( %s )", *tbbLog);
	}
	else
	{
		D_RELEASE_LOG(eLogType::D_LOG, "Loading Intel TBB fail ( %s )", *tbbLog);
	}
}

void dooms::memory::MemoryManager::Init()
{
	CheckIsIntelTBBLoaded();
}

void dooms::memory::MemoryManager::Update()
{
}

void dooms::memory::MemoryManager::OnEndOfFrame()
{
}
