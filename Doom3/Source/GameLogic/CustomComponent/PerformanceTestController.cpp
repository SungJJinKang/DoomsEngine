#include "PerformanceTestController.h"

#define D_DEBUG_CPU_VENDOR_PROFILER
#include <Profiler/CPUVendorProfiler.h>

void doom::PerformanceTestController::InitComponent()
{
	CPU_VENDOR_PROFILER_RESUME;
}

void doom::PerformanceTestController::UpdateComponent()
{
	if (doom::time::MainTimer::GetCurrentFrameCount() > 2000)
	{
		CPU_VENDOR_PROFILER_PAUSE;
		EXIT_PROGRAM;
	}
}

void doom::PerformanceTestController::OnEndOfFrame_Component()
{
}
