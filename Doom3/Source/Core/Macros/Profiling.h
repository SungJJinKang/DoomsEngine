#pragma once

#if defined(DEBUG_MODE)

#include "../Profiler/Profiler.h"

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer) doom::profiler::Profiler::StartElapsedTimeProfiling(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name) doom::profiler::Profiler::EndElapsedTimeProfiling(name)
#endif

//	HOW TO USE D_ACCUMULATE_PROFILING
//
//	
//	for ( int i = 0 ; i < 100 ; i ++ )
//	{
//		D_START_ACCUMULATE_PROFILING("Some Statements1", eLayer::Rendering);
//		Some Statements1 <- We want elapsed time for iteration, but i don't want log for every loop
//		D_END_ACCUMULATE_PROFILING("Some Statements1");
//
//		D_START_ACCUMULATE_PROFILING("Some Statements2", eLayer::Rendering);
//		Some Statements2 <- We want elapsed time for iteration, but i don't want log for every loop
//		D_END_ACCUMULATE_PROFILING("Some Statements2");
//	}	
//
//	D_EMIT_ACCUMULATE_PROFILING("Some Statements1"); <- finally Log Total elapsed time
//	D_EMIT_ACCUMULATE_PROFILING("Some Statements2"); <- finally Log Total elapsed time
//	 
//

#ifndef D_START_ACCUMULATE_PROFILING
#define D_START_ACCUMULATE_PROFILING(name, layer) doom::profiler::Profiler::StartAccumulationTimeProfiling(name, layer)
#endif

#ifndef D_END_ACCUMULATE_PROFILING
#define D_END_ACCUMULATE_PROFILING(name) doom::profiler::Profiler::EndAccumulationTimeProfiling(name)
#endif

#ifndef D_EMIT_ACCUMULATE_PROFILING
#define D_EMIT_ACCUMULATE_PROFILING(name) doom::profiler::Profiler::EmitAcculationProfiling(name)
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
