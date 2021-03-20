#pragma once

#if defined(DEBUG_MODE)
#include "../Profiler/Profiler.h"
#define D_START_PROFILING(name, layer) doom::profiler::Profiler::StartProfiling(name, layer)
#define D_END_PROFILING(name) doom::profiler::Profiler::EndProfiling(name)
#else
#define D_START_PROFILING(name, layer)
#define D_END_PROFILING(name)
#endif
