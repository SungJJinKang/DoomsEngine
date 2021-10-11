#pragma once

#include <CompilerMacros.h>
#include "MacrosHelper.h"

#include <iostream>
#include <chrono>

#include <OS/OS.h>

#ifdef DEBUG_MODE

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





#else

#define D_START_PROFILING(name, layer)
#define D_END_PROFILING(name)
#define D_START_ACCUMULATE_PROFILING(name, layer)
#define D_END_ACCUMULATE_PROFILING(name)
#define D_EMIT_ACCUMULATE_PROFILING(name)

#endif


#ifndef D_PROFILING_IN_RELEASE

#define D_PROFILING_IN_RELEASE(PROFILING_TAG, FUNCTION)																																										\
																																																							\
const auto CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME) = std::chrono::high_resolution_clock::now();																															\
const auto CONCAT(PROFILING_TAG, _START) = CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME);																																		\
FUNCTION;																																																					\
const auto CONCAT(PROFILING_TAG, _END) = std::chrono::high_resolution_clock::now();																																			\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																			\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START));											\
																																																							\
static auto CONCAT(PROFILING_TAG, _EX_TICK_TIME) = std::chrono::high_resolution_clock::now();																																\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																					\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME) - CONCAT(PROFILING_TAG, _EX_TICK_TIME));							\
CONCAT(PROFILING_TAG, _EX_TICK_TIME) = CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME);																																			\
if ( CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() >= 1000.0 )																																								\
{																																																							\
	std::cout << "Profiler ( " MAKE_STRING(PROFILING_TAG) << " ) : " << ( CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME).count() / ( CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() / 1000 ) ) << " (ms)" << std::endl;			\
	CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																																\
	CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																														\
}																																																					
#endif
