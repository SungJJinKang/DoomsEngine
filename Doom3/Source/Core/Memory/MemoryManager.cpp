#include "MemoryManager.h"

#include <oneapi/tbb/tbbmalloc_proxy.h>
#include <EngineGUI/PrintText.h>

void dooms::memory::MemoryManager::CheckIsIntelTBBLoaded() const
{
	char** tbbLog;
	const int isTbbSuccess = TBB_malloc_replacement_log(&tbbLog);
	D_ASSERT_LOG(isTbbSuccess == 0, *tbbLog);
	if(isTbbSuccess == 0)
	{
		dooms::ui::PrintText("Intel TBB is successfully loaded ( %s )", *tbbLog);
	}
	else
	{
		dooms::ui::PrintText("Loading Intel TBB fail ( %s )", *tbbLog);
	}
}

void dooms::memory::MemoryManager::Init(const int argc, char* const* const argv)
{
	CheckIsIntelTBBLoaded();
}

void dooms::memory::MemoryManager::Update()
{
}

void dooms::memory::MemoryManager::OnEndOfFrame()
{
}
