#include <GameEngineEntryPoint.h>

#include <oneapi/tbb/tbbmalloc_proxy.h>

int main()
{
	char** tbbLog;
	const int isTbbSuccess = TBB_malloc_replacement_log(&tbbLog);
	D_ASSERT_LOG(isTbbSuccess == 0, *tbbLog);

	return dooms::GameEngineEntryPoint();
}

