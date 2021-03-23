#pragma once

#if defined(DEBUG_MODE)

#include "../Profiler/Profiler.h"

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer) doom::profiler::Profiler::StartProfiling(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name) doom::profiler::Profiler::EndProfiling(name)
#endif

#else
#define D_START_PROFILING
#define D_END_PROFILING(name)
#endif
