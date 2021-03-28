#pragma once

#if defined(DEBUG_MODE)

#include "../Profiler/Profiler.h"

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer) doom::profiler::Profiler::StartProfiling(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name) doom::profiler::Profiler::EndProfiling(name)
#endif

#ifndef D_START_INSTANT_PROFILING
#define D_START_INSTANT_PROFILING auto instantProfilingStart = std::chrono::high_resolution_clock::now();
#endif

#ifndef D_END_INSTANT_PROFILING
#define D_END_INSTANT_PROFILING \
auto instantProfilingEnd = std::chrono::high_resolution_clock::now(); \
std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(instantProfilingEnd - instantProfilingStart).count() << std::endl;
#endif





#else
#define D_START_PROFILING(name, layer)
#define D_END_PROFILING(name)
#define D_START_INSTANT_PROFILING
#define D_END_INSTANT_PROFILING
#endif
