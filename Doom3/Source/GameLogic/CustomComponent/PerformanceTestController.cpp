#include "PerformanceTestController.h"

#define D_DEBUG_CPU_VENDOR_PROFILER
#include <Profiler/CPUVendorProfiler.h>

void dooms::PerformanceTestController::InitComponent()
{
	CPU_VENDOR_PROFILER_RESUME;
}

void dooms::PerformanceTestController::UpdateComponent()
{
	if (dooms::time::MainTimer::GetSingleton()->GetCurrentFrameCount() > 2000)
	{
		CPU_VENDOR_PROFILER_PAUSE;
		EXIT_PROGRAM;
	}
}

void dooms::PerformanceTestController::OnEndOfFrame_Component()
{
}
